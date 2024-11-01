//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fWelcomeDialog.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/ProjectManager.h"
#include "Project/Documents/MachineConfig.h"
#include "Project/Documents/Settings.h"
#include "Settings/ThemeManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmWelcomeDialog::TfrmWelcomeDialog(TComponent* Owner)
: TFrame(Owner)
, m_LoadingPanel(nullptr)
{
    // load the themes
    ThemeManager::LoadStyles(cmbThemes);
    // load the machines
    cmbMachines->Items->Clear();
    std::vector<String> machines;
    Project::MachineConfig::GetMachinesList(machines);
    for (const auto& machine : machines)
    {
        cmbMachines->Items->Add(machine);
        if (machine.Pos("ZX Spectrum") > 0)
        {
            cmbMachines->ItemIndex = cmbMachines->Items->Count - 1;
        }
    }
}
//---------------------------------------------------------------------------
__fastcall TfrmWelcomeDialog::~TfrmWelcomeDialog()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::OnEvent(const Event& event)
{
    if (event.Id == "project.loading.tick" && m_LoadingPanel)
    {
        m_LoadingPanel->Tick();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectClick(TObject *Sender)
{
    panStartNew->Color = panButtons->Color;
    panStartNew->Visible = true;
    panButtons->Visible = false;
    edtName->Text = "";
    edtName->SetFocus();
    for (int i = 0; i < cmbMachines->Items->Count; i++)
    {
        if (cmbMachines->Items->Strings[i] == theAppSettings.DefaultMachine)
        {
            cmbMachines->ItemIndex = i;
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::btnCreateClick(TObject *Sender)
{
    panButtons->Visible = true;
    panStartNew->Visible = false;
    auto button = dynamic_cast<TButton*>(Sender);
    if (button && button->ModalResult == mrOk)
    {
        theProjectManager.New(edtName->Text, cmbMachines->Items->Strings[cmbMachines->ItemIndex]);
        if (FOnDone) FOnDone(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblOpenExistingProjectClick(TObject *Sender)
{
    dlgOpen->InitialDir = Services::Folders::Projects;
    if (dlgOpen->Execute())
    {
        auto ext = Services::File::Extension(dlgOpen->FileName);

        if (ext == ".agds")
        {
            theProjectManager.Open(dlgOpen->FileName);
            if (FOnDone) FOnDone(this);
        }
        else if (ext == ".agd")
        {
            // import the agd file
        }
        else
        {
            dlgInvalidProject->Execute();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::SelectionPanelOnClick(TObject *Sender)
{
    m_LoadingPanel = (TSelectionPanelFrame*)Sender;
    m_LoadingPanel->Loading = true;
    theProjectManager.Open(m_LoadingPanel->Path);
    m_LoadingPanel->Loading = false;
    m_LoadingPanel = nullptr;
    if (FOnDone) FOnDone(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::SelectionPanelOnRemoveClick(TObject *Sender)
{
    TSelectionPanelFrame* panel = (TSelectionPanelFrame*)Sender;
    theProjectManager.RemoveMostRecentlyUsedItem(panel->Name, panel->Path);
    RefreshMRUList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectMouseEnter(TObject *Sender)
{
    ((TLabel*)Sender)->Font->Color = ThemeManager::Highlight;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectMouseLeave(TObject *Sender)
{
    ((TLabel*)Sender)->Font->Color = ThemeManager::Foreground;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::cmbThemesChange(TObject *Sender)
{
    ThemeManager::SetStyle(cmbThemes->Text);
    UpdateColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblChangeThemeClick(TObject *Sender)
{
    cmbThemes->DroppedDown = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::UpdateColors()
{
    panMain->Color = ThemeManager::Background;
    panRecentProjects->Color = ThemeManager::Shadow;
    lblStartNewProject->Font->Color = ThemeManager::Foreground;
    lblOpenExistingProject->Font->Color = ThemeManager::Foreground;
    lblChangeTheme->Font->Color = ThemeManager::Foreground;
    for (auto panel : m_MostRecentlyUsedItems) panel->UpdateControl();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::RefreshMRUList()
{
    m_MostRecentlyUsedItems.clear();
    for (const auto& item : theProjectManager.GetMostRecentlyUsedList())
    {
        auto file = Services::File::Combine(Services::Folders::Documents, item.Path);
        if (Services::File::Exists(file))
        {
            NewMostRecentlyUsedItem(item.Name, item.Path, item.Machine);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::NewMostRecentlyUsedItem(const String& name, const String& path, const String& machine)
{
    auto spf = std::shared_ptr<TSelectionPanelFrame>(new TSelectionPanelFrame(this));
    m_MostRecentlyUsedItems.push_back(spf);
    spf->Parent = panRecentProjects;
    spf->Name = name;
    spf->Path = path;
    spf->Machine = machine;
    spf->OnSelectedClick = SelectionPanelOnClick;
    spf->OnRemoveClick = SelectionPanelOnRemoveClick;
    spf->Top = 1000;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::edtNameChange(TObject *Sender)
{
    auto isEmpty = edtName->Text.Trim() == "";
    auto file = ApplicationName + Services::Folders::Separator + edtName->Text;
    auto projectExists = Services::File::Exists(file);
    lblFile->Caption = file;
    lblFile->Visible = !isEmpty;
    btnCreate->Enabled = !isEmpty && !projectExists;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::edtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == vkReturn && btnCreate->Enabled)
    {
        btnCreateClick(btnCreate);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::OnActivate(TWinControl* parent)
{
    if (parent != nullptr)
    {
        ThemeManager::LoadStyles(cmbThemes);
        Parent = parent;
        Visible = true;
        dynamic_cast<TForm*>(Parent)->Caption = "Welcome to " + ApplicationName;
        RefreshMRUList();
        UpdateColors();
        m_Registrar.Subscribe<Event>(OnEvent);
    }
    else
    {
        Visible = false;
        Parent = nullptr;
        m_Registrar.Unsubscribe();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::dlgInvalidProjectButtonClicked(TObject *Sender, TModalResult ModalResult, bool &CanClose)
{
    if (ModalResult != mrClose)
    {
        // launch the agd converter
        auto dir = Services::File::PathOf(Application->ExeName);
        auto app =  Services::File::Combine(dir, "AGD Converter.exe");
        if (Services::File::Exists(app))
        {
            ShellExecute(NULL, L"open", app.c_str(), NULL, dir.c_str(), SW_SHOWNORMAL);
        }
        else
        {
            MessageDlg("The 'AGD Converter' application was not found\r\nPlease reinstall AGD Studio", mtError, TMsgDlgButtons() << mbOK, 0);
        }
    }
}
//---------------------------------------------------------------------------

