//---------------------------------------------------------------------------
#ifndef fPaletteBitmapH
#define fPaletteBitmapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Dialogs.hpp>
#include "Visuals/GraphicsBuffer.h"
#include "Visuals/GraphicsMode.h"
//---------------------------------------------------------------------------
class TfrmPaletteBitmap : public TFrame
{
__published:// IDE-managed Components
    TPanel *panColorL;
    TPanel *panColorR;
    TButton *btnSwap;
    TPanel *Panel3;
    TImage *imgLogicalColors;
    TImage *imgSystemColors;
    TLabel *lblLogicalColor;
    TLabel *lblSystemColor;
    TPanel *panLogicalColorPicker;
    TPanel *panSystemColorPicker;
    TImageList *ImageList1;
    TButton *btnPaletteLoad;
    TButton *btnPaletteSave;
    TButton *btnPaletteRestore;
    TImageList *ImageList2;
    TOpenDialog *dlgOpen;
    TSaveDialog *dlgSave;
    void __fastcall imgLogicalColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgLogicalColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgLogicalColorsMouseLeave(TObject *Sender);
    void __fastcall imgSystemColorsMouseLeave(TObject *Sender);
    void __fastcall btnPaletteRestoreClick(TObject *Sender);
    void __fastcall btnSwapClick(TObject *Sender);
    void __fastcall btnPaletteLoadClick(TObject *Sender);
    void __fastcall btnPaletteSaveClick(TObject *Sender);
private:    // User declarations
    int                         m_Pen;              // logical pen color
    int                         m_Brush;            // logical brush color
    int                         m_CursorLogical;    // mouse cursor on the logical colour picker
    int                         m_CursorPhysical;   // mouse cursor on the physical colour picker
    std::unique_ptr<TBitmap>    m_LogicalPicker;    // the picker images double buffer
    std::unique_ptr<TBitmap>    m_PhysicalPicker;   // the picker images double buffer
	Visuals::GraphicsMode&      m_GraphicsMode;     // the graphics mode used by the project
    const Visuals::Palette&     m_Palette;          // the palette used by the graphics mode

    void            __fastcall  DrawPhysicalColors() const;
    void            __fastcall  DrawLogicalColors() const;
    void            __fastcall  Update();
public:     // User declarations
                    __fastcall  TfrmPaletteBitmap(TComponent* Owner);
    void            __fastcall  Init();
	void            __fastcall  Set(Visuals::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
