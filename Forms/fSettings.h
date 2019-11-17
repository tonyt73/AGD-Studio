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
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmSettings : public TForm
{
__published:    // IDE-managed Components
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
    TImageList *ImageList1;
    TTabSheet *TabSheet1;
    TLabel *Label6;
    TPageControl *pgcBuild;
    TTabSheet *tabAssembler;
    TTabSheet *tabEmulator;
    TImageList *ImageList2;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TEdit *edtAssemblerExe;
    TEdit *edtAssemblerParams;
    TEdit *edtAssemblerPrepend;
    TButton *btnAssemblerFind;
    TEdit *edtAssemblerAppend;
    TLabel *Label11;
    TLabel *Label12;
    TEdit *edtEmulatorExe;
    TEdit *edtEmulatorParams;
    TButton *btnEmulatorFind;
    TTabSheet *tabCompiler;
    TLabel *Label13;
    TLabel *Label14;
    TEdit *edtCompilerExe;
    TEdit *edtCompilerParams;
    TButton *btnCompilerFind;
    TEdit *edtBuildMachine;
    TOpenDialog *dlgOpen;
    TEdit *edtEngineFile;
    TLabel *Label15;
    TButton *btnEngineFind;
    TTabSheet *TabSheet2;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnProfileClick(TObject *Sender);
    void __fastcall btnOkClick(TObject *Sender);
    void __fastcall cmbThemesChange(TObject *Sender);
    void __fastcall chkLoadLastProjectClick(TObject *Sender);
    void __fastcall chkWelcomeSkipOnStartupClick(TObject *Sender);
    void __fastcall btnCompilerFindClick(TObject *Sender);
    void __fastcall btnAssemblerFindClick(TObject *Sender);
    void __fastcall btnEngineFindClick(TObject *Sender);
    void __fastcall btnEmulatorFindClick(TObject *Sender);
private:    // User declarations
    String  __fastcall  FindExecutable(const String& title, const String& path) const;
    void    __fastcall  GetBuildOptions();
    void    __fastcall  SaveMachineConfig();

public:     // User declarations
            __fastcall  TfrmSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
