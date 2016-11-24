//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Camera cam(5, 45, 45);

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
	glColor3f(0.0f,1.0f,0.0f);              	//
	glBegin(GL_TRIANGLES);                      // Рисуем перед лево верх рыбки.
		glVertex3f(x, y, z + weight);           //
		glVertex3f(x, y + height, z);           //
		glVertex3f(x - length, y, z);           //
	glEnd();
	glColor3f(0.0f,1.0f,1.0f);

	glBegin(GL_TRIANGLES);                      // Рисуем перед лево низ рыбки.
		glVertex3f(x, y, z + weight);          //
		glVertex3f(x, y - height, z);          //
		glVertex3f(x - length, y, z);          //
	glEnd();
	glColor3f(1.0f,1.0f,0.5f);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево верх рыбки.
		glVertex3f(x, y, z - weight);          //
		glVertex3f(x, y + height, z);          //
		glVertex3f(x - length, y, z);          //
	glEnd();
	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево низ рыбки.
		glVertex3f(x, y, z - weight);          //
		glVertex3f(x, y - height, z);          //
		glVertex3f(x - length, y, z);          //
	glEnd();
	//Правая часть
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);                      // Рисуем перед право верх рыбки.
		glVertex3f(x, y, z + weight);          //
		glVertex3f(x, y + height, z);          //
		glVertex3f(x + length, y, z);          //
	glEnd();
	glColor3f(0.0f,1.0f,1.0f);

	glBegin(GL_TRIANGLES);                      // Рисуем перед право низ рыбки.
		glVertex3f(x, y, z + weight);          //
		glVertex3f(x, y - height, z);          //
		glVertex3f(x + length, y, z);          //
	glEnd();
	glColor3f(1.0f,1.0f,0.5f);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею правую верх рыбки.
		glVertex3f(x, y, z - weight);          //
		glVertex3f(x, y + height, z);          //
		glVertex3f(x + length, y, z);          //
	glEnd();
    glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);                      // Рисуем заднею лево низ рыбки.
		glVertex3f(x, y, z - weight);          //
		glVertex3f(x, y - height, z);          //
		glVertex3f(x + length, y, z);          //
	glEnd();
	//Хвост
	glBegin(GL_TRIANGLES);                      // Рисуем переднею.
		glVertex3f(x + length, y, z);        //
		glVertex3f(x + length + tail, y + tail, z + tailHeight);	//
		glVertex3f(x + length + tail, y - tail, z + tailHeight);           //
	glEnd();

	glBegin(GL_TRIANGLES);                      // Рисуем заднею.
		glVertex3f(x + length, y, z);        //
		glVertex3f(x + length + tail, y + tail, z - tailHeight);	//
		glVertex3f(x + length + tail, y - tail, z - tailHeight);           //
	glEnd();

}

void DrawAquarium()
{
	glColor4f(0.0f, 0.0f,1.0f, 0.2);
	GLUquadricObj* m_qObj;
	m_qObj = gluNewQuadric();
	float R = 2;

	gluSphere(m_qObj, R, 500, 500);
}

void TForm1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawFish(0,0,0);
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
//---------------------------------------------------------------------------

