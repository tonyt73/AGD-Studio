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
#include "Graphics/GraphicsBuffer.h"
#include "Graphics/GraphicsMode.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmULAplusBitmap : public TFrame
{
__published:	// IDE-managed Components
    TPanel *panColorL;
    TPanel *panColorR;
    TPanel *Panel3;
    TImage *imgLogicalColors;
    TImage *imgSystemColors;
    TLabel *lblLogicalColor;
    TLabel *lblSystemColor;
    TPanel *panPalettePicker;
    TPanel *panSystemColorPicker;
    TImageList *ImageList1;
    TButton *btnPaletteLoad;
    TButton *btnPaletteSave;
    TButton *btnPaletteRestore;
    TImageList *ImageList2;
    TSaveDialog *dlgSave;
    TOpenDialog *dlgOpen;
    void __fastcall imgLogicalColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgLogicalColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgSystemColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgLogicalColorsMouseLeave(TObject *Sender);
    void __fastcall imgSystemColorsMouseLeave(TObject *Sender);
    void __fastcall btnPaletteRestoreClick(TObject *Sender);
    void __fastcall btnPaletteSaveClick(TObject *Sender);
    void __fastcall btnPaletteLoadClick(TObject *Sender);
private:	// User declarations
    int                         m_Ink;              // logical ink color
    int                         m_Paper;            // logical paper color
    int                         m_Index;            // logical palette index
    int                         m_Cursor;           // mouse cursor on the ink/paper
    int                         m_CursorIndex;      // mouse cursor on the palette index
    int                         m_CursorPhysical;   // mouse cursor on the physical colour picker
    std::unique_ptr<TBitmap>    m_PalettePicker;    // the picker images double buffer
    std::unique_ptr<TBitmap>    m_PhysicalPicker;   // the picker images double buffer
    Agdx::GraphicsMode&         m_GraphicsMode;     // the graphics mode used by the project
    const Agdx::Palette&        m_Palette;          // the palette used by the graphics mode

    void    __fastcall  DrawSelectionBox(TBitmap* bitmap, int xs, int ys, int xe, int ye) const;
    void    __fastcall  DrawPhysicalColors() const;
    void    __fastcall  DrawPalettesColors() const;
    void    __fastcall  Update();

    int     __fastcall  GetInk(int index = -1, int ink = -1) const;
    int     __fastcall  GetPaper(int index = -1, int paper = -1) const;
public:		// User declarations
            __fastcall  TfrmULAplusBitmap(TComponent* Owner);
    void    __fastcall  Init();
    void    __fastcall  Set(Agdx::GraphicsBuffer& canvas);
};
//---------------------------------------------------------------------------
#endif
