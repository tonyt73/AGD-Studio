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
    TBevel *Bevel1;
    TBevel *Bevel2;
    TBevel *Bevel3;
    TBevel *Bevel4;
    TLabel *Label1;
    void __fastcall spdInkBlackClick(TObject *Sender);
    void __fastcall spdPaperBlackClick(TObject *Sender);
    void __fastcall spdBrightOffClick(TObject *Sender);
    void __fastcall spdFlashOffClick(TObject *Sender);
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
