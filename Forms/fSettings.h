//---------------------------------------------------------------------------

#ifndef fSettingsH
#define fSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDCustomSheetControl.hpp"
#include "LMDPageControl.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSettings : public TForm
{
__published:	// IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPanel *Panel1;
    TPageControl *pgcSettings;
    TTabSheet *tabProfile;
    TTabSheet *tabInterface;
    TTabSheet *tabMachines;
    TLabel *Label1;
    TLabel *Label4;
    TEdit *edtDeveloper;
    TComboBox *cmbMachines;
    TSpeedButton *btnProfile;
    TSpeedButton *btnInterface;
    TSpeedButton *btnMachines;
    TLabel *Label5;
    TComboBox *cmbThemes;
    TCheckBox *chkWelcomeSkipOnStartup;
    TLabel *Label2;
    TCheckBox *chkWelcomeSkipOnClose;
    TLabel *Label3;
    TCheckBox *chkLoadLastProject;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnProfileClick(TObject *Sender);
    void __fastcall btnOkClick(TObject *Sender);
    void __fastcall cmbThemesChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
