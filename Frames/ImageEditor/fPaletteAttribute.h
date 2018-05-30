//---------------------------------------------------------------------------
#ifndef fPaletteAttributeH
#define fPaletteAttributeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "Graphics/AttributeGraphicsBuffer.h"
//---------------------------------------------------------------------------
class TfrmPaletteAttribute : public TFrame
{
__published:	// IDE-managed Components
    TLabel *lblPaletteInk;
    TLabel *lblPalettePaper;
    TSpeedButton *spdInkBlack;
    TSpeedButton *spdInkBlue;
    TSpeedButton *spdInkRed;
    TSpeedButton *spdInkPurple;
    TSpeedButton *spdInkGreen;
    TSpeedButton *spdInkCyan;
    TSpeedButton *spdInkYellow;
    TSpeedButton *spdInkWhite;
    TSpeedButton *spdInkTransparent;
    TSpeedButton *spdPaperBlack;
    TSpeedButton *spdPaperBlue;
    TSpeedButton *spdPaperRed;
    TSpeedButton *spdPaperPurple;
    TSpeedButton *spdPaperGreen;
    TSpeedButton *spdPaperCyan;
    TSpeedButton *spdPaperYellow;
    TSpeedButton *spdPaperWhite;
    TSpeedButton *spdPaperTransparent;
    TSpeedButton *spdBrightOff;
    TSpeedButton *spdBrightOn;
    TSpeedButton *spdBrightTransparent;
    TSpeedButton *spdFlashOff;
    TSpeedButton *spdFlashOn;
    TSpeedButton *spdFlashTransparent;
    TLabel *lblPaletteBright;
    TLabel *lblPaletteFlash;
    TImage *imgPaletteTransparent;
    TLabel *lblPaletteTransparent;
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmPaletteAttribute(TComponent* Owner);


};
//---------------------------------------------------------------------------
#endif
