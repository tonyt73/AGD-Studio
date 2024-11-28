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
    auto defaultMachine = theAppSettings.DefaultMachine.LowerCase().Trim();
    cmbMachines->ItemIndex = -1;
    for (const auto& machine : machines)
    {
        cmbMachines->Items->Add(machine);
        if (machine.LowerCase().Trim() == defaultMachine)
        {
            cmbMachines->ItemIndex = cmbMachines->Items->Count - 1;
        }
    }
    if (cmbMachines->ItemIndex == -1)
    {
        cmbMachines->ItemIndex = 0;
    }
    imgMachineCross->Hint = StringReplace(imgMachineCross->Hint, "\\r", char(13), TReplaceFlags() << rfReplaceAll);
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
    lblImportAGD->Visible = false;
    imgImportAGD->Visible = false;
    panStartNew->Visible = true;
    edtName->Text = "";
    edtName->SetFocus();
    btnCreate->Caption = "Create";
    UpdateUI(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblImportAGDClick(TObject *Sender)
{
    lblStartNewProject->Visible = false;
    imgStartNewProject->Visible = false;
    lblImportFile->Visible = true;
    edtImportFile->Visible = true;
    btnImportFile->Visible = true;
    panStartNew->Visible = true;
    edtName->Text = "";
    btnCreate->Caption = "Import";
    btnImportFile->SetFocus();
    UpdateUI(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::btnCreateClick(TObject *Sender)
{
    lblImportAGD->Visible = true;
    imgImportAGD->Visible = true;
    lblStartNewProject->Visible = true;
    imgStartNewProject->Visible = true;
    panButtons->Visible = true;
    panStartNew->Visible = false;
    auto button = dynamic_cast<TButton*>(Sender);
    if (button && button->ModalResult == mrOk)
    {
        theProjectManager.New(edtName->Text, cmbMachines->Text);
        if (FOnDone) FOnDone(this);
        if (edtImportFile->Visible) {
            Application->ProcessMessages();
            theProjectManager.Import(edtImportFile->Text);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblOpenExistingProjectClick(TObject *Sender)
{
    dlgOpenAGDS->InitialDir = Services::Folders::Projects;
    if (dlgOpenAGDS->Execute())
    {
        auto ext = Services::File::Extension(dlgOpenAGDS->FileName);

        if (ext == ".agds")
        {
            theProjectManager.Open(dlgOpenAGDS->FileName);
            if (FOnDone) FOnDone(this);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::SelectionPanelOnClick(TObject *Sender)
{
    m_LoadingPanel = (TSelectionPanelFrame*)Sender;
    m_LoadingPanel->Loading = true;
    theProjectManager.Open(m_LoadingPanel->Path, m_LoadingPanel->Machine);
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
    lblImportAGD->Font->Color = ThemeManager::Foreground;
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
    UpdateUI();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::edtImportFileChange(TObject *Sender)
{
    auto name = Services::File::NameWithoutExtension(edtImportFile->Text);
    edtName->Text = edtName->Text.Trim() != "" ? name : edtName->Text.Trim();
    UpdateUI();
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
void __fastcall TfrmWelcomeDialog::btnImportFileClick(TObject *Sender)
{
    dlgImportAGD->InitialDir = Services::Folders::Projects;
    if (dlgImportAGD->Execute())
    {
        auto name = Services::File::NameWithoutExtension(dlgImportAGD->FileName);
        edtName->Text = name;
        edtImportFile->Text = dlgImportAGD->FileName;
        UpdateUI();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::cmbMachinesChange(TObject *Sender)
{
    UpdateUI();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::UpdateUI(bool updateMachine)
{
    panStartNew->Color = panButtons->Color;
    panStartNew->Visible = true;
    panButtons->Visible = false;
    if (updateMachine) {
        for (int i = 0; i < cmbMachines->Items->Count; i++)
        {
            if (cmbMachines->Items->Strings[i] == theAppSettings.DefaultMachine)
            {
                cmbMachines->ItemIndex = i;
                break;
            }
        }
    }

    auto name = edtName->Text.Trim();
    auto isProjectEmpty = name == "";
    auto path = Services::Folders::GetFolder(Services::Folders::lpApplication, "Projects" + Services::Folders::Separator + name);
    auto projectExists = Services::Folders::Exists(path);
    lblFile->Caption = Services::Folders::GetFolderRelativeTo(Services::Folders::lpDocuments, path);
    lblFile->Visible = !isProjectEmpty;

    if (lblStartNewProject->Visible) {
        // new project
        lblImportFile->Visible = false;
        edtImportFile->Visible = false;
        btnImportFile->Visible = false;
        imgMachineTick->Visible = false;
        imgMachineCross->Visible = false;
        imgImportFileTick->Visible = false;
        imgImportFileCross->Visible = false;
        btnCreate->Enabled = !isProjectEmpty && !projectExists;
    } else {
        // import agd file
        auto importFile = edtImportFile->Text.Trim();
        auto isImportEmpty = importFile == "";
        auto importerExists = Services::File::Exists(Services::Folders::GetFolder(Services::Folders::lpApplication, "Importers" + Services::Folders::Separator + cmbMachines->Text + ".json"));
        imgImportFileTick->Visible = !isImportEmpty && Services::File::Exists(importFile);
        imgImportFileCross->Visible = !isImportEmpty && !Services::File::Exists(importFile);
        imgMachineTick->Visible = importerExists;
        imgMachineCross->Visible = !imgMachineTick->Visible;
        btnCreate->Enabled = !isProjectEmpty && !projectExists && importerExists;
    }
    imgProjectNameTick->Visible = !isProjectEmpty && btnCreate->Enabled;
    imgProjectNameCross->Visible = !isProjectEmpty && !btnCreate->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::imgMachineCrossClick(TObject *Sender)
{
    auto folder = Services::Folders::GetFolder(Services::Folders::lpApplication, "Importers");
    ShellExecute(NULL, L"open", L"", NULL, folder.c_str(), SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

