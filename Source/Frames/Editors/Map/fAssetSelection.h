//---------------------------------------------------------------------------
#ifndef fAssetSelectionH
#define fAssetSelectionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "Project/Documents/Images.h"
//---------------------------------------------------------------------------
class TfrmAssetSelection : public TFrame
{
__published:    // IDE-managed Components
    TFlowPanel *panList;
    TMenuItem *mnuToggleLabels;
    TPopupMenu *popMenu;
    TScrollBox *sbxList;
    void __fastcall mnuToggleLabelsClick(TObject *Sender);
    void __fastcall sbxListMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall sbxListResize(TObject *Sender);

private:    // User declarations
    void __fastcall OnImageClick(TObject* Sender);
    int  __fastcall FindSelected();

    typedef void __fastcall (__closure *TNotifyImageOnSelectionEvent)(Project::ImageDocument* document);
    TNotifyImageOnSelectionEvent    FOnImageClick;

public:    // User declarations
            __fastcall TfrmAssetSelection(TComponent* Owner);

    void    __fastcall  Clear();
    void    __fastcall  Add(Project::ImageDocument* image, bool enabled = true);
    void    __fastcall  Select(const Project::ImageDocument* image);
    void    __fastcall  UpdateDocument(const Project::ImageDocument* image);
    void    __fastcall  Next();
    void    __fastcall  Prev();

    __property  TNotifyImageOnSelectionEvent    OnImageSelection = { read = FOnImageClick, write = FOnImageClick };
};
//---------------------------------------------------------------------------
#endif
