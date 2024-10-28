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
#include "Visuals/GraphicsBuffer.h"
//---------------------------------------------------------------------------
class TfrmPaletteAttribute : public TFrame
{
__published:    // IDE-managed Components
    TBevel *Bevel1;
    TBevel *Bevel2;
    TBevel *Bevel3;
    TBevel *Bevel4;
    TImage *imgPaletteTransparent;
    TLabel *Label1;
    TLabel *lblPaletteBright;
    TLabel *lblPaletteFlash;
    TLabel *lblPalettePaper;
    TLabel *lblPaletteTransparent;
    TSpeedButton *spdBrightOff;
    TSpeedButton *spdBrightOn;
    TSpeedButton *spdBrightTransparent;
    TSpeedButton *spdFlashOff;
    TSpeedButton *spdFlashOn;
    TSpeedButton *spdFlashTransparent;
    TSpeedButton *spdInkBlack;
    TSpeedButton *spdInkBlue;
    TSpeedButton *spdInkCyan;
    TSpeedButton *spdInkGreen;
    TSpeedButton *spdInkPurple;
    TSpeedButton *spdInkRed;
    TSpeedButton *spdInkTransparent;
    TSpeedButton *spdInkWhite;
    TSpeedButton *spdInkYellow;
    TSpeedButton *spdPaperBlack;
    TSpeedButton *spdPaperBlue;
    TSpeedButton *spdPaperCyan;
    TSpeedButton *spdPaperGreen;
    TSpeedButton *spdPaperPurple;
    TSpeedButton *spdPaperRed;
    TSpeedButton *spdPaperTransparent;
    TSpeedButton *spdPaperWhite;
    TSpeedButton *spdPaperYellow;
    void __fastcall spdBrightOffClick(TObject *Sender);
    void __fastcall spdFlashOffClick(TObject *Sender);
    void __fastcall spdInkBlackClick(TObject *Sender);
    void __fastcall spdPaperBlackClick(TObject *Sender);

private:    // User declarations
    int                 m_Ink;
    int                 m_Paper;
    int                 m_Bright;
    int                 m_Flash;
public:     // User declarations
            __fastcall  TfrmPaletteAttribute(TComponent* Owner);

    void    __fastcall  Set(Visuals::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
