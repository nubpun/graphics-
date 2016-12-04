//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Camera cam(10, 45, 45);
float bubblePos = 0;

const int fishSize = 5;
float fishAlfa[fishSize] = {0.17, 0.21, 0, 0.13};
float fishAngle[fishSize]={0,30,-30,60, -60};
float fishTrans[fishSize]={3, 2.25, 2.8, 3.7, 2.2};
float ar[fishSize][3] = {{0, 0, 0}, {0, 2, 0}, {0, 1, 0}, {0, -2, 0},  {-1, -2, 1}};
float R = 5;
GLuint  texture[11];  // ������ ��� �������� �������
BOOL TForm1::bSetupPixelFormat(HDC hDC)

{
	PIXELFORMATDESCRIPTOR pfd; //������� ���������

  int pixelformat;

  pfd.nSize = sizeof (PIXELFORMATDESCRIPTOR); //������ ���������

  pfd.nVersion = 1;  //������ ���������

  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

  pfd.iLayerType =  PFD_MAIN_PLANE;  //��� �����������

  pfd.iPixelType = PFD_TYPE_RGBA;  //������ �������� �����

  pfd.cColorBits = 16;  //������� �����

  pfd.cDepthBits = 16;  //������ ������ �������

  pfd.cAccumBits = 0; //����� ����� ������� ���������� � ������ ������������

  pfd.cStencilBits = 0;  //������ ������ ���������

  if (!(pixelformat=ChoosePixelFormat(hDC, &pfd))) {

    MessageBox(NULL, "���������� ������� ������ ��������", "Error", MB_OK);

    return false;

  }

  if (!SetPixelFormat (hDC, pixelformat, &pfd)) {

    MessageBox(NULL, "���������� ���������� ������ ��������", "Error", MB_OK);

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
	glEnable(GL_LIGHT0);  //�������� ��������� 0
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
hDC = GetDC(Handle); //Handle � ���������� ���� (hwnd � WinAPI)
if (!bSetupPixelFormat(hDC)) //������������� ������ ��������
  return;
ghRC = wglCreateContext(hDC); //������� �������� ���������������
wglMakeCurrent(hDC, ghRC);  //������ ��� �������
glClearColor(1, 1, 1, 0.0); //���� ������ ��� ��������
glEnable(GL_COLOR_MATERIAL);  //��������� �������� ���� ��������
glEnable(GL_DEPTH_TEST);  //���� ������� ��� ���������� �����������

glEnable(GL_ALPHA_TEST);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
light_on();
glEnable(GL_TEXTURE_2D);    // ���������� ��������� ��������
LoadGLTextures();           // ����� ������� ������� �������
}
//---------------------------------------------------------------------------

void light_off()
{
	glDisable(GL_LIGHT0); // ��������� ���������
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
	glBegin(GL_TRIANGLES);                      // ������ ����� ���� ���� �����.
		glTexCoord2f(0.0f, 0.0f); 	glVertex3f(x, y, z + weight);           //
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f(x, y + height, z);           //
		glTexCoord2f(1.0f, 0.0f); 	glVertex3f(x - length, y, z);           //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLES);                      // ������ ����� ���� ��� �����.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y - height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLES);                      // ������ ������ ���� ���� �����.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLES);                      // ������ ������ ���� ��� �����.
	 glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x - length, y, z);          //
	glEnd();
	//������ �����
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLES);                      // ������ ����� ����� ���� �����.
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_TRIANGLES);                      // ������ ����� ����� ��� �����.
	 glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + weight);          //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_TRIANGLES);                      // ������ ������ ������ ���� �����.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y + height, z);          //
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_TRIANGLES);                      // ������ ������ ���� ��� �����.
	   glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z - weight);          //
	   glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y - height, z);          //
	   glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length, y, z);          //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	//�����
	glBegin(GL_TRIANGLES);                      // ������ ��������.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + length, y, z);        //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x + length + tail, y + tail, z + tailHeight);	//
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length + tail, y - tail, z + tailHeight);           //
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_TRIANGLES);                      // ������ ������.
	  glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + length, y, z);        //
	  glTexCoord2f(0.0f, 1.0f);	glVertex3f(x + length + tail, y + tail, z - tailHeight);	//
	  glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + length + tail, y - tail, z - tailHeight);           //
	glEnd();

}

void DrawAquarium()
{

  float r = R / 20;//������ ������
  float bubbleR = r;
  //	������ ����� � ���������
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
   //������ ��������� ������

	glColor4f(0.50f, 0.7f, 1.0f, 1.0);
	glass = gluNewQuadric();
	glPushMatrix();
	glTranslatef(2 * r, -R + 2 * r + bubblePos, 2 * r);
	gluSphere(glass, bubbleR, 500, 500);
	gluDeleteQuadric(glass);
	glPopMatrix();
   //������ ��������
	 glColor4f(0.0f, 0.0f, 1.0f, 0.2);
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
	AUX_RGBImageRec *text[11]; //�������� ��������� �� ������ ��������
	text[0] = auxDIBImageLoad("1.bmp"); //���� � ��������
	text[1] = auxDIBImageLoad("2.bmp"); //���� � ��������
	text[2] = auxDIBImageLoad("3.bmp"); //���� � ��������
	text[3] = auxDIBImageLoad("4.bmp"); //���� � ��������
	text[4] = auxDIBImageLoad("5.bmp"); //���� � ��������
	text[5] = auxDIBImageLoad("6.bmp"); //���� � ��������
	text[6] = auxDIBImageLoad("7.bmp"); //���� � ��������
	text[7] = auxDIBImageLoad("8.bmp"); //���� � ��������
	text[8] = auxDIBImageLoad("9.bmp"); //���� � ��������
	text[9] = auxDIBImageLoad("10.bmp"); //���� � ��������
	glGenTextures(10, &texture[0]); //���-�� �������
	//�������� ��� OpenGL, ��� ������ �������� ����� ��������� � ������ �������� �������. ���� ����� ������������� ��������� �������, ���������� ������ ������ ������ ��������, ����������� ������� �� ����
	for (int i = 0; i < 10 ; i++) {
		glBindTexture(GL_TEXTURE_2D, texture[i]);
	//�������� ��� OpenGL, ��� ���������� �������� ����� ���������
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//��������, ����� ��� ���������� ������������ � �������, ����� ����������� �� ������, 
	//��������������, ������ ��� ������, ��� ������ �������� (������������� GL_LINEAR, �� ��� ��������� ����������� ����� ����������� GL_NEAREST)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, text[i]->sizeX, text[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, text[i]->data);
		//�������� ����������� ��������
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

