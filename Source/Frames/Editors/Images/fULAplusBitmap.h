//---------------------------------------------------------------------------
#ifndef fULAplusBitmapH
#define fULAplusBitmapH
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
class TfrmULAplusBitmap : public TFrame
{
__published:    // IDE-managed Components
    TButton *btnPaletteLoad;
    TButton *btnPaletteRestore;
    TButton *btnPaletteSave;
    TImage *imgLogicalColors;
    TImage *imgSystemColors;
    TImageList *ImageList1;
    TImageList *ImageList2;
    TLabel *lblLogicalColor;
    TLabel *lblSystemColor;
    TOpenDialog *dlgOpen;
    TPanel *panColorL;
    TPanel *panColorR;
    TPanel *Panel3;
    TPanel *panPalettePicker;
    TPanel *panSystemColorPicker;
    TSaveDialog *dlgSave;
    void __fastcall btnPaletteLoadClick(TObject *Sender);
    void __fastcall btnPaletteRestoreClick(TObject *Sender);
    void __fastcall btnPaletteSaveClick(TObject *Sender);
    void __fastcall imgLogicalColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgLogicalColorsMouseLeave(TObject *Sender);
    void __fastcall imgLogicalColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseLeave(TObject *Sender);
    void __fastcall imgSystemColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private:    // User declarations
    unsigned char               m_Ink;              // logical ink color
    unsigned char               m_Paper;            // logical paper color
    unsigned char               m_Index;            // logical palette index
    unsigned char               m_Cursor;           // mouse cursor on the ink/paper
    unsigned char               m_CursorIndex;      // mouse cursor on the palette index
    int                         m_CursorPhysical;   // mouse cursor on the physical colour picker
    std::unique_ptr<TBitmap>    m_PalettePicker;    // the picker images double buffer
    std::unique_ptr<TBitmap>    m_PhysicalPicker;   // the picker images double buffer
    Visuals::GraphicsMode&      m_GraphicsMode;     // the graphics mode used by the project
    const Visuals::Palette&     m_Palette;          // the palette used by the graphics mode

    void            __fastcall  DrawSelectionBox(TBitmap* bitmap, int xs, int ys, int xe, int ye) const;
    void            __fastcall  DrawPhysicalColors() const;
    void            __fastcall  DrawPalettesColors() const;
    void            __fastcall  Update() override;

    unsigned char   __fastcall  GetInk(int index = -1, int ink = -1) const;
    unsigned char   __fastcall  GetPaper(int index = -1, int paper = -1) const;
public:        // User declarations
                    __fastcall  TfrmULAplusBitmap(TComponent* Owner) override;
    void            __fastcall  Init();
    void            __fastcall  Set(Visuals::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
