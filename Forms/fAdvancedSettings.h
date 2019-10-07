//---------------------------------------------------------------------------

#ifndef fAdvancedSettingsH
#define fAdvancedSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXPanels.hpp>
#include "ElTreeInplaceEditors.hpp"
#include "ElXPThemedControl.hpp"
#include "ElXTree.hpp"
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImageList.hpp>
//---------------------------------------------------------------------------
class TfrmAdvancedSettings : public TForm
{
__published:    // IDE-managed Components
    TPanel *panButtons;
    TCardPanel *crdPanels;
    TCard *Card1;
    TCard *Card2;
    TButton *Button1;
    TButton *Button2;
    TElXTree *ElXTree1;
    TSplitter *splSplitter;
    TImageList *ImageList1;
    TTreeView *TreeView1;
private:    // User declarations
public:        // User declarations
    __fastcall TfrmAdvancedSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAdvancedSettings *frmAdvancedSettings;
//---------------------------------------------------------------------------
#endif
