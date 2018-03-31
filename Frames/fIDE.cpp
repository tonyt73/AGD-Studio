//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fAbout.h"
#include "fIDE.h"
#include "fEditorImage.h"
#include "fEditorCode.h"
#include "fEditorMap.h"
#include "ProjectManager.h"
#include "DocumentEditorFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDDckSite"
#pragma link "LMDInsPropInsp"
#pragma link "LMDInsPropPage"
#pragma link "ElTreeInplaceEditors"
#pragma link "ElXPThemedControl"
#pragma link "ElXTree"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmIDE::TfrmIDE(TComponent* Owner)
: TFrame(Owner)
{
    RegisterDocumentEditors();
}
//---------------------------------------------------------------------------
__fastcall TfrmIDE::~TfrmIDE()
{
    if (Application && Application->MainForm)
    {
        Application->MainForm->Menu = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::RegisterDocumentEditors()
{
    // TODO: Do this another way
    // ie. by document class type to editor?
    DocumentEditorFactory::Register("Assets\\Files", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Game\\Code", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Game\\Events", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Assets\\Sounds", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Assets\\Images", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Assets\\Sprites", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Assets\\Objects", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Assets\\Tiles", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Assets\\Maps",  &TfrmEditorMap::Create);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnActivate()
{
    if (Application && Application->MainForm)
    {
        Application->MainForm->Menu = mnuMain;
        Application->MainForm->Caption = "AGDX Studio";
    }
    ThemeSettings::ReapplyStyle();
    Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    tvProject->BackGroundColor = StyleServices()->GetStyleColor(scGenericGradientBase);
    dsIDE->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileExitExecute(TObject *Sender)
{
    theProjectManager.Save();
    if (Application && Application->MainForm)
    {
        Application->MainForm->Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCopyExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCutExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditPasteExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectNewExecute(TObject *Sender)
{
    theProjectManager.Save();
    static auto docNo = 0;
    auto dp = new TLMDDockPanel(this);
    Document* doc = nullptr;
    switch (docNo % 4)
    {
        case 0:
        {
            auto name = "new sprite " + IntToStr(docNo++);
            doc = theProjectManager.Add("Image", "Sprite", name);
            dp->Tag = (int)doc;
            doc->DockPanel = dp;
            UpdateProperties(doc);
            dp->Caption = name;
            break;
        }
        case 1:
        {
            auto name = "new event " + IntToStr(docNo++);
            doc = theProjectManager.Add("Text", "Event", name);
            dp->Tag = (int)doc;
            doc->DockPanel = dp;
            UpdateProperties(doc);
            dp->Caption = name;
            break;
        }
        case 2:
        {
            auto name = "new tile " + IntToStr(docNo++);
            doc = theProjectManager.Add("Image", "Tile", name);
            dp->Tag = (int)doc;
            doc->DockPanel = dp;
            UpdateProperties(doc);
            dp->Caption = name;
            break;
        }
        case 3:
        {
            auto name = "new object " + IntToStr(docNo++);
            doc = theProjectManager.Add("Image", "Object", name);
            dp->Tag = (int)doc;
            doc->DockPanel = dp;
            UpdateProperties(doc);
            dp->Caption = name;
            break;
        }
    }
    DocumentEditorFactory::Create(doc, dp);
    dp->ClientKind = dkDocument;
    dsIDE->DockControl(dp, dsIDE->SpaceZone);
    dp->OnClose = OnDocumentClose;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectOpenExecute(TObject *Sender)
{
    theProjectManager.Save();

}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectSaveExecute(TObject *Sender)
{
    theProjectManager.Save();
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectCloseExecute(TObject *Sender)
{
    theProjectManager.Save();
    if (FOnFormClose)
    {
        Application->MainForm->Menu = nullptr;
        FOnFormClose(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actHelpAboutExecute(TObject *Sender)
{
    (new TfrmAbout(this))->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditUndoExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditRedoExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::UpdateProperties(Document* document)
{
    const auto properties = document->GetPropertyInfo();
    for (auto it : properties)
    {
        lmdProperties->RegisterPropCategory(it.second.category, it.first);
    }
    lmdProperties->Objects->SetOne(document);
    lmdProperties->ExpandAllCategories();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectExpandAllClick(TObject *Sender)
{
    tvProject->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectCollapseAllClick(TObject *Sender)
{
    tvProject->FullCollapse();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectShowLinesClick(TObject *Sender)
{
    tvProject->ShowLines = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectHideLinesClick(TObject *Sender)
{
    tvProject->ShowLines = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectShowFoldersClick(TObject *Sender)
{
    tvProject->FullCollapse();
    for (auto node : tvProject->Items)
    {
        if (node->Level < 2)
        {
            node->Expand(false);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::lmdPropertiesClick(TObject *Sender)
{
    if (lmdProperties->Objects->Count >= 1)
    {
        auto doc = dynamic_cast<Document*>(lmdProperties->Objects->Item[0]);
        if (doc != nullptr && lmdProperties->ActiveItem != nullptr)
        {
            lblPropertyInfo->Caption = doc->GetPropertyInfo(lmdProperties->ActiveItem->PropName);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectItemSelectedChange(TObject *Sender, TElXTreeItem *Item)
{
    if (Item->Tag)
    {
        auto doc = (Document*)((NativeInt)Item->Tag);
        UpdateProperties(doc);
        auto dockPanel = static_cast<TLMDDockPanel*>(doc->DockPanel);
        if (dockPanel)
        {
            dockPanel->Activate();
            dockPanel->Show();
            dockPanel->SetFocus();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnDocumentClose(TObject *Sender, TLMDockPanelCloseAction& action)
{
    auto dockPanel = dynamic_cast<TLMDDockPanel*>(Sender);
    if (dockPanel)
    {
        action = caFree;    // this will call the editor destructor, which can optional save the document
        Document* doc = (Document*)dockPanel->Tag;
        doc->DockPanel = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectDblClick(TObject *Sender)
{
    if (tvProject->Selected)
    {
        auto doc = (Document*)((NativeInt)tvProject->Selected->Tag);
        if (doc && doc->DockPanel == nullptr)
        {
            auto dp = new TLMDDockPanel(this);
            if (DocumentEditorFactory::Create(doc, dp))
            {
                dp->Caption = doc->Name;
                dp->Tag = (NativeInt)doc;
                doc->DockPanel = dp;
                UpdateProperties(doc);
                dp->ClientKind = dkDocument;
                dsIDE->DockControl(dp, dsIDE->SpaceZone);
                dp->OnClose = OnDocumentClose;
                dp->Activate();
                dp->Show();
                dp->SetFocus();
            }
            else
            {
                delete dp;
            }
        }
    }
}
//---------------------------------------------------------------------------

