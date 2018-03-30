//---------------------------------------------------------------------------
#ifndef fWelcomeDialogH
#define fWelcomeDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
#include "fSelectionPanel.h"
//---------------------------------------------------------------------------
class TfrmWelcomeDialog : public TFrame
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TLabel *lblStartNewProject;
	TImage *imgStartNewProject;
	TImage *imgLogo;
	TLabel *lblTitle;
	TLabel *lblVersion;
	TPanel *panRecentProjects;
	TImage *imgConfigure;
	TLabel *lblConfigure;
	TImage *imgDownArrow;
	TPopupMenu *popConfigure;
	TMenuItem *Settings1;
	TMenuItem *CheckforUpdates1;
    TOpenTextFileDialog *dlgOpen;
    TPanel *panButtons;
    TLabel *lblOpenExistingProject;
    TLabel *lblImportAGDSnapshot;
    TImage *imgImportTommyGunProject;
    TImage *imgOpenExistingProject;
    TComboBox *cmbThemes;
    TLabel *lblChangeTheme;
    TImage *imgChangeTheme;
    TPanel *panStartNew;
    TButton *btnCancel;
    TButton *btnCreate;
    TComboBox *cmbMachines;
    TLabel *lblMachines;
    TLabel *Label1;
    TEdit *edtName;
    TLabel *lblFile;
	void __fastcall lblStartNewProjectMouseEnter(TObject *Sender);
	void __fastcall lblStartNewProjectMouseLeave(TObject *Sender);
	void __fastcall cmbThemesChange(TObject *Sender);
	void __fastcall lblStartNewProjectClick(TObject *Sender);
	void __fastcall lblOpenExistingProjectClick(TObject *Sender);
	void __fastcall lblImportAGDSnapshotClick(TObject *Sender);
	void __fastcall lblConfigureClick(TObject *Sender);
	void __fastcall lblChangeThemeClick(TObject *Sender);
    void __fastcall btnCreateClick(TObject *Sender);
    void __fastcall edtNameChange(TObject *Sender);
    void __fastcall edtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// Function declarations
	void 	__fastcall 	SelectionPanelOnClick(TObject *Sender);
	void 	__fastcall 	SelectionPanelOnRemoveClick(TObject *Sender);
	void 	__fastcall 	UpdateColors();
	void 	__fastcall 	RefreshMRUList();
	void 	__fastcall 	NewMostRecentlyUsedItem(const String& name, const String& path);

private:	// Member declarations
	std::list<std::shared_ptr<TSelectionPanelFrame>>    m_MostRecentlyUsedItems;

private:	// Events
	TNotifyEvent    	FOnDone;


public:		// User declarations
			__fastcall	TfrmWelcomeDialog(TComponent* Owner);

	void    __fastcall  Initialise();

	// TODO: property to set Project Manager
	//       use prjmgr to new, open, import and load recent projects

	__property	TNotifyEvent OnDone = { read = FOnDone, write = FOnDone };
};
//---------------------------------------------------------------------------
#endif
