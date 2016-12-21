//---------------------------------------------------------------------------
 #include <GL/glaux.h>
 #pragma comment (lib, "glaux.lib")
#ifndef Unit1H
#define Unit1H

#include <vcl.h>
#include <cmath>

#include <ExtCtrls.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);

private:	// User declarations
	HGLRC ghRC;  // ��������� �� �������� ��������������� (Rendering Context)
	HDC   hDC; // ���������� (��������) ����������
public:		// User declarations
void TForm1::Scale(double sx, double sy);
void TForm1::Rotate(double w);
void TForm1::InitFigure();
	void TForm1::Draw();
	void moveCamera();
	__fastcall TForm1(TComponent* Owner);
	BOOL bSetupPixelFormat(HDC hDC);

	GLvoid LoadGLTextures();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
