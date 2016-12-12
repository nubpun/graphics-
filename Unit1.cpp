//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Camera cam(13, 45, 45);
float bubblePos = 0;

const int fishSize = 5;
float fishAlfa[fishSize] = {0.17, 0.21, 0, 0.13};
float fishAngle[fishSize]={0,30,-30,60, -60};
float fishTrans[fishSize]={3, 2.25, 2.8, 3.7, 2.2};
float ar[fishSize][3] = {{0, 0, 0}, {0, 2, 0}, {0, 1, 0}, {0, -2, 0},  {-1, -2, 1}};
float R = 6;
GLuint  texture[11];  // Массив для хранения текстур
BOOL TForm1::bSetupPixelFormat(HDC hDC)

{
	PIXELFORMATDESCRIPTOR pfd; //Создаем структуру

  int pixelformat;

  pfd.nSize = sizeof (PIXELFORMATDESCRIPTOR); //Размер структуры

  pfd.nVersion = 1;  //Версия структуры

  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

  pfd.iLayerType =  PFD_MAIN_PLANE;  //Тип поверхности

  pfd.iPixelType = PFD_TYPE_RGBA;  //Формат указания цвета

  pfd.cColorBits = 16;  //Глубина цвета

  pfd.cDepthBits = 16;  //Размер буфера глубины

  pfd.cAccumBits = 0; //Общее число битовых плоскостей в буфере аккумулятора

  pfd.cStencilBits = 0;  //Размер буфера трафарета

  if (!(pixelformat=ChoosePixelFormat(hDC, &pfd))) {

    MessageBox(NULL, "Невозможно выбрать формат пикселей", "Error", MB_OK);

    return false;

  }

  if (!SetPixelFormat (hDC, pixelformat, &pfd)) {

    MessageBox(NULL, "Невозможно установить формат пикселей", "Error", MB_OK);

    return false;

  }

  return true;

}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
void light_on()
{
	float pos[4]= {0,0, 2, -1};
	float dir[3]= {0,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	glEnable(GL_LIGHT0);  //Включили освещение 0
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
hDC = GetDC(Handle); //Handle – дескриптор окна (hwnd в WinAPI)
if (!bSetupPixelFormat(hDC)) //Устанавливаем формат пикселей
  return;
ghRC = wglCreateContext(hDC); //Создаем контекст воспроизведения
wglMakeCurrent(hDC, ghRC);  //Делаем его текущим
glClearColor(1, 1, 1, 0.0); //Цвет экрана при очищении
glEnable(GL_COLOR_MATERIAL);  //Разрешаем задавать цвет объектам
glEnable(GL_DEPTH_TEST);  //Тест глубины для объемности изображения

glEnable(GL_ALPHA_TEST);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
light_on();
glEnable(GL_TEXTURE_2D);    // Разрешение наложение текстуры
LoadGLTextures();           // Вызов функции импорта текстур
}
//---------------------------------------------------------------------------

void light_off()
{
	glDisable(GL_LIGHT0); // отключаем освещение
}
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if(ghRC)
	{
		wglMakeCurrent(hDC,0);
		wglDeleteContext(ghRC);
	}
	if(hDC) ReleaseDC(Handle, hDC);
}
//---------------------------------------------------------------------------
  void __fastcall TForm1::FormResize(TObject *Sender)
{
	 moveCamera();
}
//---------------------------------------------------------------------------
using namespace std;
void DrawFish(float x, float y, float z)
{
	float height = 0.6;
	float weight = 0.5;
	float length = 1;
	float tail = 0.3;
	float tailHeight = 0.01;

	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, texture[0]);            	//
	glBegin(GL_TRIANGLES);                      // Рисуем перед лево верх рыбки.
		glTexCoord2f(0.0f, 0.0f); 	glVertex3f(x, y, z + weight);           //
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f(x, y + height, z);           //
		glTexCoord2f(1.0f, 0.0f); 	glVertex3f(x - length, y, z);           //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLES);                      // Рисуем перед лево низ рыбки.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y - height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево верх рыбки.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево низ рыбки.
	 glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();
	//Правая часть
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLES);                      // Рисуем перед право верх рыбки.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_TRIANGLES);                      // Рисуем перед право низ рыбки.
	 glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею правую верх рыбки.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево низ рыбки.
	   glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	   glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	   glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	//Хвост
	glBegin(GL_TRIANGLES);                      // Рисуем переднею.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + length, y, z);        //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x + length + tail, y + tail, z + tailHeight);	//
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length + tail, y - tail, z + tailHeight);           //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + length, y, z);        //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x + length + tail, y + tail, z - tailHeight);	//
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length + tail, y - tail, z - tailHeight);           //
	glEnd();

}

void DrawAquarium()
{

  float r = R / 20;//Радиус камней
  float bubbleR = r;
  //	Рисуем камни в аквариуме
  glPushMatrix();
  glColor4f(0.6, 0.4, 0.2, 1.0);
  glTranslatef(0, -R + r , 0);

	GLUquadricObj* glass;
	glass = gluNewQuadric();
	gluSphere(glass, r, 500, 500);
	gluDeleteQuadric(glass);
   glPopMatrix();

   glPushMatrix();
	glTranslatef(2 * r, -R + 2 * r , 0);
	glass = gluNewQuadric();
	gluSphere(glass, r, 500, 500);
	gluDeleteQuadric(glass);
   glPopMatrix();

   glPushMatrix();
	glTranslatef(0, -R + 2 * r , 2 * r);
	glass = gluNewQuadric();
	gluSphere(glass, r, 500, 500);
	gluDeleteQuadric(glass);
   glPopMatrix();

   glPushMatrix();
	glTranslatef(2 * r, -R + 2 * r , 2 * r);
	glass = gluNewQuadric();
	gluSphere(glass, r, 500, 500);
	gluDeleteQuadric(glass);
   glPopMatrix();
   //рисуем воздушный пузырь

	glColor4f(0.50f, 0.7f, 1.0f, 1.0);
	glass = gluNewQuadric();
	glPushMatrix();
	glTranslatef(2 * r, -R + 2 * r + bubblePos, 2 * r);
	gluSphere(glass, bubbleR, 500, 500);
	gluDeleteQuadric(glass);
	glPopMatrix();
   //Рисуем аквариум
   double teta = 0.2;
	 glColor4f(0.0f, 0.0f, 1.0f, teta);
	glass = gluNewQuadric();
	gluSphere(glass, R, 500, 500);
	gluDeleteQuadric(glass);


}

void TForm1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < fishSize;i++) {
		glPushMatrix();
		glRotatef(fishAngle[i], 0, 1, 0);
		glPushMatrix();
		glTranslatef(fishTrans[i],0,0);
		glRotatef(90, 0, 1, 0);
		if(i % 2 == 0)
			glTranslatef(0,0,cos(fishAlfa[i]) / 3);
		else
			glTranslatef(0,0,sin(fishAlfa[i]) / 2);
		DrawFish(ar[i][0], ar[i][1], ar[i][2]);
		glPopMatrix();
		glPopMatrix();
	}

	DrawAquarium();
	SwapBuffers(hDC);
}



void __fastcall TForm1::FormPaint(TObject *Sender)
{
	Draw();
}
//---------------------------------------------------------------------------

void TForm1::moveCamera(){
  double x, y, dx, dy;
  x = Form1->Left;
  y = Form1->Top;
  dx = Form1->Width;
  dy = Form1->Height;
  glViewport(x, y, dx, dy);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0, dx/dy, 0.1f, 200.f);
  point eye = cam.getEye();
  point sky = cam.getNorm();
  gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, sky.x, sky.y, sky.z);
  glMatrixMode(GL_MODELVIEW);
}

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key){
		case(VK_RIGHT):{
			cam.rotate(0, -1);
            moveCamera();
            Draw();
			break;
		}
		case(VK_LEFT):{
            cam.rotate(0, 1);
            moveCamera();
            Draw();
			break;
		}
		case(VK_DOWN):{
            cam.rotate(1, 0);
            moveCamera();
            Draw();
			break;
		}
		case(VK_UP):{
            cam.rotate(-1, 0);
            moveCamera();
            Draw();
			break;
		}
		case(VK_ADD):
        case(VK_OEM_PLUS):{
			cam.zoom(-1);
            moveCamera();
            Draw();
            break;
		}
        case(VK_SUBTRACT ):
        case(VK_OEM_MINUS):{
			cam.zoom(1);
            moveCamera();
            Draw();
			break;
		}
        default:
            break;
   }
}

GLvoid TForm1::LoadGLTextures()
{
	AUX_RGBImageRec *text[11]; //Создание указателя на нужную текстуру
	text[0] = auxDIBImageLoad("1.bmp"); //Путь к текстуре
	text[1] = auxDIBImageLoad("2.bmp"); //Путь к текстуре
	text[2] = auxDIBImageLoad("3.bmp"); //Путь к текстуре
	text[3] = auxDIBImageLoad("4.bmp"); //Путь к текстуре
	text[4] = auxDIBImageLoad("5.bmp"); //Путь к текстуре
	text[5] = auxDIBImageLoad("6.bmp"); //Путь к текстуре
	text[6] = auxDIBImageLoad("7.bmp"); //Путь к текстуре
	text[7] = auxDIBImageLoad("8.bmp"); //Путь к текстуре
	text[8] = auxDIBImageLoad("9.bmp"); //Путь к текстуре
	text[9] = auxDIBImageLoad("10.bmp"); //Путь к текстуре
	glGenTextures(10, &texture[0]); //Кол-во текстур
	//Указание для OpenGL, что первая текстура будет храниться в первом элементе массива. Если нужно импортировать несколько текстур, достаточно менять только первый аргумент, дублировать функцию не надо
	for (int i = 0; i < 10 ; i++) {
		glBindTexture(GL_TEXTURE_2D, texture[i]);
	//Указание для OpenGL, что конкретная текстура будет двумерной
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//Указание, какой тип фильтрации использовать в случаях, когда изображение на экране, 
	//соответственно, больше или меньше, чем данная текстура (рекомендуется GL_LINEAR, но для медленных компьютеров можно попробовать GL_NEAREST)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, text[i]->sizeX, text[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, text[i]->data);
		//Создание фактической текстуры
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	for (int i=0; i < fishSize; i++) {
			fishAngle[i] -= 0.6;
			if (fishAngle[i]>360-fishAngle[i]) {
				fishAngle[i]=0;
			}
			fishAlfa[i] -= 0.07;
		}


	if(bubblePos > 1.8 * R )
		bubblePos = 0.0;
	else
		bubblePos += 0.1;
	Draw();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
      Form2->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N1Click(TObject *Sender)
{
	Form3->ShowModal();
}
//---------------------------------------------------------------------------

