//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fSettings.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/MachineConfig.h"
#include "Project/Documents/Settings.h"
#include "Settings/ThemeManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomPanel"
#pragma link "LMDCustomPanelFill"
#pragma link "LMDCustomParentPanel"
#pragma link "LMDCustomSheetControl"
#pragma link "LMDPageControl"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmSettings::TfrmSettings(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::FormCreate(TObject *Sender)
{
    if (theAppSettings.Developer.Trim() != "")
    {
        edtDeveloper->Text = theAppSettings.Developer;
    }
    chkWelcomeSkipOnStartup->Checked = theAppSettings.WelcomeSkipOnStartup;
    chkWelcomeSkipOnClose->Checked = theAppSettings.WelcomeSkipOnClose;
    chkLoadLastProject->Checked = theAppSettings.LoadLastProject;
    chkWelcomeSkipOnStartupClick(nullptr);
    chkLoadLastProjectClick(nullptr);
    //panButtons->Color = ThemeManager::Background;
    // load the themes
    ThemeManager::LoadStyles(cmbThemes);
    // load the machines
    cmbMachines->Items->Clear();
    std::vector<String> machines;
    Project::MachineConfig::GetMachinesList(machines);
    for (const auto& machine : machines)
    {
        cmbMachines->Items->Add(machine);
        if (machine == theAppSettings.DefaultMachine || (cmbMachines->ItemIndex == -1 && machine.Pos("ZX Spectrum") > 0))
        {
            cmbMachines->ItemIndex = cmbMachines->Items->Count - 1;
        }
    }
    pgcSettings->ActivePage = tabProfile;
    pgcBuild->ActivePage = tabCompiler;
    // set the build options
    GetBuildOptions();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnProfileClick(TObject *Sender)
{
    pgcSettings->TabIndex = ((TControl*)Sender)->Tag;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnOkClick(TObject *Sender)
{
    theAppSettings.WelcomeSkipOnStartup = chkWelcomeSkipOnStartup->Checked;
    theAppSettings.WelcomeSkipOnClose = chkWelcomeSkipOnClose->Checked;
    theAppSettings.LoadLastProject = chkLoadLastProject->Checked;
    theAppSettings.Developer = edtDeveloper->Text;
    theAppSettings.DefaultMachine = cmbMachines->Items->Strings[cmbMachines->ItemIndex];
    SaveMachineConfig();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::cmbThemesChange(TObject *Sender)
{
    ThemeManager::SetStyle(cmbThemes->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::chkLoadLastProjectClick(TObject *Sender)
{
    if (chkLoadLastProject->Checked)
    {
        chkWelcomeSkipOnStartup->Checked = true;
        chkWelcomeSkipOnStartup->Enabled = false;
    }
    else
    {
        chkWelcomeSkipOnStartup->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::chkWelcomeSkipOnStartupClick(TObject *Sender)
{
    if (chkWelcomeSkipOnStartup->Checked)
    {
        chkLoadLastProject->Enabled = true;
    }
    else
    {
        chkLoadLastProject->Checked = false;
        chkLoadLastProject->Enabled = false;
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmSettings::FindExecutable(const String& title, const String& path) const
{
    auto folder = path;
    if (folder == "" || !Services::Folders::Exists(folder))
    {
        folder = Services::File::Combine(Services::Folders::Application, "Compilers");
    }

    dlgOpen->InitialDir = folder;
    dlgOpen->Title = title;
    if (dlgOpen->Execute())
    {
        auto file = dlgOpen->FileName;
        auto relFilePath = Services::Folders::GetFolderRelativeTo(Services::Folders::lpApplication, file);
        if (relFilePath != file)
        {
            return relFilePath;
        }
        return file;
    }
    else
    {
        return path;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnCompilerFindClick(TObject *Sender)
{
    edtCompilerExe->Text = FindExecutable("Locate AGD Compiler", edtCompilerExe->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnEngineFindClick(TObject *Sender)
{
    dlgOpen->FilterIndex = 1;
    edtEngineFile->Text = FindExecutable("Locate AGD Engine File", edtEngineFile->Text);
    dlgOpen->FilterIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnAssemblerFindClick(TObject *Sender)
{
    edtAssemblerExe->Text = FindExecutable("Locate Assembler", edtAssemblerExe->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::btnEmulatorFindClick(TObject *Sender)
{
    edtEmulatorExe->Text = FindExecutable("Locate Emulator", edtEmulatorExe->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::GetBuildOptions()
{
    const auto& cfg = theDocumentManager.ProjectConfig()->MachineConfiguration();
    edtBuildMachine->Text = cfg.Name;
    edtCompilerExe->Text = cfg.Compiler.Path;
    edtCompilerParams->Text = cfg.Compiler.Parameters;
    edtEngineFile->Text = cfg.Engine.Path;
    edtAssemblerExe->Text = cfg.Assembler.Path;
    edtAssemblerParams->Text = cfg.Assembler.Parameters;
    edtAssemblerPrepend->Text = cfg.Assembler.Prepend;
    edtAssemblerAppend->Text = cfg.Assembler.Append;
    edtEmulatorExe->Text = cfg.Emulator.Path;
    edtEmulatorParams->Text = cfg.Emulator.Parameters;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::SaveMachineConfig()
{
    auto& cfg = theDocumentManager.ProjectConfig()->WritableMachineConfiguration();
    cfg.Compiler = Project::MachineConfig::ToolInfo(edtCompilerExe->Text, edtCompilerParams->Text);
    cfg.Engine = Project::MachineConfig::ToolInfo(edtEngineFile->Text, "");
    cfg.Assembler = Project::MachineConfig::ToolInfoExt(edtAssemblerExe->Text, edtAssemblerParams->Text, edtAssemblerPrepend->Text, edtAssemblerAppend->Text);
    cfg.Emulator = Project::MachineConfig::ToolInfo(edtEmulatorExe->Text, edtEmulatorParams->Text);
}
//---------------------------------------------------------------------------

