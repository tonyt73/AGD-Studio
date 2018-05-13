//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fSettings.h"
#include "Settings.h"
#include "MachineConfig.h"
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
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettings::cmbThemesChange(TObject *Sender)
{
    TStyleManager::SetStyle(cmbThemes->Text);
    appSettings.ActiveStyle = cmbThemes->Text;
}
//---------------------------------------------------------------------------


