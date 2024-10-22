//---------------------------------------------------------------------------
#ifndef AssetSelectionH
#define AssetSelectionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "Project/ImageDocument.h"
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
    void __fastcall OnImageClick(TObject* Sender);
    int             FindSelected();

    typedef void (__closure *TNotifyImageOnSelectionEvent)(Project::ImageDocument* document);
    TNotifyImageOnSelectionEvent    FOnImageClick;

public:    // User declarations
                    TfrmAssetSelection(TComponent* Owner);

    void            Clear();
    void            Add(Project::ImageDocument* image, bool enabled = true);
    void            Select(const Project::ImageDocument* image);
    void            UpdateDocument(const Project::ImageDocument* image);
    void            Next();
    void            Prev();

    __property  TNotifyImageOnSelectionEvent    OnImageSelection = { read = FOnImageClick, write = FOnImageClick };
};
//---------------------------------------------------------------------------
#endif
