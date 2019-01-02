//---------------------------------------------------------------------------
#ifndef AssetSelectionH
#define AssetSelectionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "ImageDocuments.h"
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfrmAssetSelection : public TFrame
{
__published:    // IDE-managed Components
    TScrollBox *sbxList;
    TFlowPanel *panList;
    TPopupMenu *popMenu;
    TMenuItem *mnuToggleLabels;
    void __fastcall sbxListMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall sbxListResize(TObject *Sender);
    void __fastcall mnuToggleLabelsClick(TObject *Sender);
private:    // User declarations
    void    __fastcall  OnImageClick(TObject* Sender);
    int     __fastcall  FindSelected();

    typedef void __fastcall (__closure *TNotifyImageOnSelectionEvent)(ImageDocument* document);
    TNotifyImageOnSelectionEvent    FOnImageClick;

public:        // User declarations
            __fastcall  TfrmAssetSelection(TComponent* Owner);

    void    __fastcall  Clear();
    void    __fastcall  Add(ImageDocument* image);
    void    __fastcall  Select(ImageDocument const * const image);
    void    __fastcall  Next();
    void    __fastcall  Prev();

    __property  TNotifyImageOnSelectionEvent    OnImageSelection = { read = FOnImageClick, write = FOnImageClick };
};
//---------------------------------------------------------------------------
#endif
