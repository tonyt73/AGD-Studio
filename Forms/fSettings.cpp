//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fSettings.h"
#include "Project/DocumentManager.h"
#include "Settings/Settings.h"
#include "MachineConfig.h"
#include "System/File.h"
#include "System/Path.h"
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
    if (appSettings.Developer.Trim() != "")
    {
        edtDeveloper->Text = appSettings.Developer;
    }
    chkWelcomeSkipOnStartup->Checked = appSettings.WelcomeSkipOnStartup;
    chkWelcomeSkipOnClose->Checked = appSettings.WelcomeSkipOnClose;
    chkLoadLastProject->Checked = appSettings.LoadLastProject;
    chkWelcomeSkipOnStartupClick(nullptr);
    chkLoadLastProjectClick(nullptr);
    //panButtons->Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    // load the themes
    cmbThemes->Items->Clear();
    auto sl = std::make_unique<TStringList>();
    for (auto i = 0; i < TStyleManager::StyleNames.Length; i++)
    {
        if (TStyleManager::StyleNames[i] != "Windows")
        {
            sl->Add(TStyleManager::StyleNames[i]);
        }
    }
    sl->Sort();
    const String style = appSettings.ActiveStyle;
    for (auto i = 0; i < sl->Count; i++)
    {
        cmbThemes->Items->Add(sl->Strings[i]);
        if (sl->Strings[i] == style)
        {
            cmbThemes->ItemIndex = cmbThemes->Items->Count - 1;
        }
    }
    // load the machines
    cmbMachines->Items->Clear();
    std::vector<String> machines;
    MachineConfig::GetMachinesList(machines);
    for (const auto& machine : machines)
    {
        cmbMachines->Items->Add(machine);
        if (machine == appSettings.DefaultMachine || (cmbMachines->ItemIndex == -1 && machine.Pos("ZX Spectrum") > 0))
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
    appSettings.WelcomeSkipOnStartup = chkWelcomeSkipOnStartup->Checked;
    appSettings.WelcomeSkipOnClose = chkWelcomeSkipOnClose->Checked;
    appSettings.LoadLastProject = chkLoadLastProject->Checked;
    appSettings.Developer = edtDeveloper->Text;
    appSettings.DefaultMachine = cmbMachines->Items->Strings[cmbMachines->ItemIndex];
    SaveMachineConfig();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::cmbThemesChange(TObject *Sender)
{
    TStyleManager::SetStyle(cmbThemes->Text);
    appSettings.ActiveStyle = cmbThemes->Text;
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
    if (folder == "" || !System::Path::Exists(folder))
    {
        folder = System::File::Combine(System::Path::Application, "Compilers");
    }

    dlgOpen->InitialDir = folder;
    dlgOpen->Title = title;
    if (dlgOpen->Execute())
    {
        auto file = dlgOpen->FileName;
        auto relFilePath = System::Path::GetFolderRelativeTo(System::Path::lpApplication, file);
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
    cfg.Compiler = MachineConfig::ToolInfo(edtCompilerExe->Text, edtCompilerParams->Text);
    cfg.Assembler = MachineConfig::ToolInfoExt(edtAssemblerExe->Text, edtAssemblerParams->Text, edtAssemblerPrepend->Text, edtAssemblerAppend->Text);
    cfg.Emulator = MachineConfig::ToolInfo(edtEmulatorExe->Text, edtEmulatorParams->Text);
}
//---------------------------------------------------------------------------

