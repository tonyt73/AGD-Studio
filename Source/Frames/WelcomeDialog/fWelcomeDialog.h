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
#include <Vcl.Buttons.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
#include "fSelectionPanel.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmWelcomeDialog : public TFrame
{
__published:    // IDE-managed Components
    TButton *btnCancel;
    TButton *btnCreate;
    TComboBox *cmbMachines;
    TComboBox *cmbThemes;
    TEdit *edtName;
    TImage *imgChangeTheme;
    TImage *imgLogo;
    TImage *imgOpenExistingProject;
    TImage *imgStartNewProject;
    TLabel *Label1;
    TLabel *lblChangeTheme;
    TLabel *lblFile;
    TLabel *lblMachines;
    TLabel *lblOpenExistingProject;
    TLabel *lblStartNewProject;
    TMenuItem *CheckforUpdates1;
    TMenuItem *Settings1;
    TOpenTextFileDialog *dlgOpen;
    TPanel *panButtons;
    TPanel *Panel1;
    TPanel *panMain;
    TPanel *panRecentProjects;
    TPanel *panStartNew;
    TPopupMenu *popConfigure;
    TTaskDialog *dlgInvalidProject;
    void __fastcall btnCreateClick(TObject *Sender);
    void __fastcall cmbThemesChange(TObject *Sender);
    void __fastcall dlgInvalidProjectButtonClicked(TObject *Sender, TModalResult ModalResult, bool &CanClose);
    void __fastcall edtNameChange(TObject *Sender);
    void __fastcall edtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall lblChangeThemeClick(TObject *Sender);
    void __fastcall lblOpenExistingProjectClick(TObject *Sender);
    void __fastcall lblStartNewProjectClick(TObject *Sender);
    void __fastcall lblStartNewProjectMouseEnter(TObject *Sender);
    void __fastcall lblStartNewProjectMouseLeave(TObject *Sender);

private:    // Function declarations
    void     __fastcall     SelectionPanelOnClick(TObject *Sender);
    void     __fastcall     SelectionPanelOnRemoveClick(TObject *Sender);
    void     __fastcall     UpdateColors();
    void     __fastcall     RefreshMRUList();
    void     __fastcall     NewMostRecentlyUsedItem(const String& name, const String& path, const String& machine);
    void     __fastcall     OnEvent(const Event& event);

private:    // Member declarations
    Registrar                                           m_Registrar;
    std::list<std::shared_ptr<TSelectionPanelFrame>>    m_MostRecentlyUsedItems;
    TSelectionPanelFrame*                               m_LoadingPanel;

private:    // Events
    TNotifyEvent            FOnDone;

public:        // User declarations
            __fastcall      TfrmWelcomeDialog(TComponent* Owner);
            __fastcall     ~TfrmWelcomeDialog();

    void    __fastcall      OnActivate(TWinControl* parent);

    __property TNotifyEvent OnDone = { read = FOnDone, write = FOnDone };
};
//---------------------------------------------------------------------------
#endif
