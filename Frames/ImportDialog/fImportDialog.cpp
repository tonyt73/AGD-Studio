//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Project/ProjectManager.h"
#include "System/File.h"
#include "fImportDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmImportDialog *frmImportDialog;
//---------------------------------------------------------------------------
__fastcall TfrmImportDialog::TfrmImportDialog(TComponent* Owner)
: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::Initialise()
{
    dynamic_cast<TForm*>(Parent)->Caption = "Import an AGD Project File";
    UpdateColors();
    // TODO: Load the machine names into the combo box
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::UpdateColors()
{
    Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    lblFile->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblProjectName->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblMachine->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblDestMachine->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::edtFileChange(TObject *Sender)
{
    btnImport->Enabled = System::File::Exists(edtFile->Text.Trim()) && edtProjectName->Text.Trim() != "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::btnOpenClick(TObject *Sender)
{
    dlgImport->InitialDir = System::Path::Projects;
    if (dlgImport->Execute())
    {
        auto prevName = System::File::NameWithoutExtension(edtFile->Text);
        edtFile->Text = dlgImport->FileName;
        auto projectName = System::File::NameWithoutExtension(edtFile->Text);
        if (edtProjectName->Text.Trim() == "" || prevName == edtProjectName->Text)
        {
            edtProjectName->Text = projectName;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::btnImportClick(TObject *Sender)
{
    auto file = dlgImport->FileName;
    auto name = System::File::NameWithoutExtension(file);
    if (!System::Path::Exists(System::Path::lpProjects, name))
    {
        if (FOnDone) FOnDone(this);
        theProjectManager.New(name, "ZX Spectrum 256x192 16 Colour");
        theProjectManager.Import(file);
    }
    else
    {
        // TODO: Better dialog box
        ShowMessage("Project already exists!");
        if (FOnDone) FOnDone(nullptr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportDialog::btnCancelClick(TObject *Sender)
{
    if (FOnDone) FOnDone(nullptr);
}
//---------------------------------------------------------------------------
