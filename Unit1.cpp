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

	glEnable(GL_LIGHTING);  //Разрешаем освещение
	glEnable(GL_LIGHT0);  //Включили освещение 0


	float p2[4]= {0,0,0, 0};
	glLightfv(GL_LIGHT1,GL_POSITION, p2);  //Установка позиции освещения
	glEnable(GL_LIGHT1);  //Включили освещение 0


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
	glDisable(GL_LIGHT1); // отключаем освещение
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
void DrawFish()
{
	glBegin(GL_QUADS);                      // Рисуем куб
		glColor3f(0.0f,1.0f,0.0f);              // Зеленый
		glVertex3f( 0.5f, 0.5f,-0.5f);          // Право верх квадрата (Верх)
		glVertex3f(-0.5f, 0.5f,-0.5f);          // Лево верх
		glVertex3f(-0.5f, 0.5f, 0.5f);          // Лево низ
		glVertex3f( 0.5f, 0.5f, 0.5f);          // Право низ

		glColor3f(1.0f,0.5f,0.0f);              // Оранжевый
		glVertex3f( 0.5f,-0.5f, 0.5f);          // Верх право квадрата (Низ)
		glVertex3f(-0.5f,-0.5f, 0.5f);          // Верх лево
		glVertex3f(-0.5f,-0.5f,-0.5f);          // Низ лево
		glVertex3f( 0.5f,-0.5f,-0.5f);          // Низ право

        glColor3f(1.0f,0.0f,0.0f);              // Красный
		glVertex3f( 0.5f, 0.5f, 0.5f);          // Верх право квадрата (Перед)
		glVertex3f(-0.5f, 0.5f, 0.5f);          // Верх лево
		glVertex3f(-0.5f,-0.5f, 0.5f);          // Низ лево
		glVertex3f( 0.5f,-0.5f, 0.5f);          // Низ право

		glColor3f(1.0f,1.0f,0.0f);              // Желтый
		glVertex3f( 0.5f,-0.5f,-0.5f);          // Верх право квадрата (Зад)
		glVertex3f(-0.5f,-0.5f,-0.5f);          // Верх лево
		glVertex3f(-0.5f, 0.5f,-0.5f);          // Низ лево
		glVertex3f( 0.5f, 0.5f,-0.5f);          // Низ право

		glColor3f(0.0f,0.0f,1.0f);              // Синий
		glVertex3f(-0.5f, 0.5f, 0.5f);          // Верх право квадрата (Лево)
		glVertex3f(-0.5f, 0.5f,-0.5f);          // Верх лево
		glVertex3f(-0.5f,-0.5f,-0.5f);          // Низ лево
		glVertex3f(-0.5f,-0.5f, 0.5f);          // Низ право

		glColor3f(1.0f,0.0f,1.0f);              // Фиолетовый
		glVertex3f( 0.5f, 0.5f,-0.5f);          // Верх право квадрата (Право)
		glVertex3f( 0.5f, 0.5f, 0.5f);          // Верх лево
		glVertex3f( 0.5f,-0.5f, 0.5f);          // Низ лево
		glVertex3f( 0.5f,-0.5f,-0.5f);          // Низ право
	glEnd();
}

void DrawAquarium()
{
	glColor4f(0.0f, 0.0f,1.0f, 0.1);
	GLUquadricObj* m_qObj;
	m_qObj = gluNewQuadric();
	gluSphere(m_qObj, 2.0f, 500, 500);
}


void TForm1::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	light_on();
	DrawFish();
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

