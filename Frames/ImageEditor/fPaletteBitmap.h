//---------------------------------------------------------------------------
#ifndef fPaletteBitmapH
#define fPaletteBitmapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Graphics/GraphicsBuffer.h"
//---------------------------------------------------------------------------
class TfrmPaletteBitmap : public TFrame
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TImage *Image1;
    TButton *Button1;
private:	// User declarations
    int                 m_Pen;
    int                 m_Brush;
public:		// User declarations
            __fastcall  TfrmPaletteBitmap(TComponent* Owner);
    void    __fastcall  Set(Agdx::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
