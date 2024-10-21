//---------------------------------------------------------------------------
#ifndef fPaletteMonoAttributeH
#define fPaletteMonoAttributeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "Graphics/GraphicsBuffer.h"
//---------------------------------------------------------------------------
class TfrmPaletteMonoAttribute : public TFrame
{
__published:    // IDE-managed Components
    TSpeedButton *spdInkBlack;
    TSpeedButton *spdInkGreen;
    TBevel *Bevel1;
    TLabel *Label1;
private:    // User declarations
public:     // User declarations
            __fastcall  TfrmPaletteMonoAttribute(TComponent* Owner);

    void    __fastcall  Set(Agdx::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
