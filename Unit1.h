//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <vcl.h>
#include <cmath>

#include <ExtCtrls.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include "Camera.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	
private:	// User declarations
	HGLRC ghRC;  // указатель на контекст воспроизведения (Rendering Context)
	HDC   hDC; // дескриптор (контекст) устройства
public:		// User declarations
void TForm1::Scale(double sx, double sy);
void TForm1::Rotate(double w);
void TForm1::InitFigure();
	void TForm1::Draw();
	    void moveCamera();
	__fastcall TForm1(TComponent* Owner);
	BOOL bSetupPixelFormat(HDC hDC);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
