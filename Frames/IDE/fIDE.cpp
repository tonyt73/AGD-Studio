//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fAbout.h"
#include "fIDE.h"
#include "fNewImage.h"
#include "fSettings.h"
#include "fEditorImage.h"
#include "fEditorCode.h"
#include "fEditorMap.h"
#include "ProjectManager.h"
#include "DocumentEditorFactory.h"
#include "Messaging/Messaging.h"
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
    DocumentEditorFactory::Register("Game\\Events", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Game\\Messages", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Game\\Sounds", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Game\\Output", &TfrmEditorCode::Create);
    DocumentEditorFactory::Register("Images\\Sprites", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Images\\Objects", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Images\\Tiles", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Images\\Character Set", &TfrmEditorImage::Create);
    DocumentEditorFactory::Register("Game\\Map",  &TfrmEditorMap::Create);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnActivate()
{
    if (Application && Application->MainForm)
    {
        Application->MainForm->Menu = mnuMain;
        Application->MainForm->Caption = ApplicationName;
    }
    ThemeSettings::ReapplyStyle();
    Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    tvProject->BackGroundColor = StyleServices()->GetStyleColor(scGenericGradientBase);
    dsIDE->Invalidate();
    RefreshMruList();

    ::Messaging::Bus::Subscribe<ErrorMessage>(OnMessageString);
    ::Messaging::Bus::Subscribe<WarningMessage>(OnMessageString);
    ::Messaging::Bus::Subscribe<InformationMessage>(OnMessageString);
    ::Messaging::Bus::Subscribe<DebugMessage>(OnMessageString);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnMessageString(const OnMessage& message)
{
    const String Types[4] = { "Info  : ", "Warn : ", "Error: ", "Debug: " };
    memMessages->Lines->Add(Types[message.Type] + message.Message);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCopyExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.copy"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCutExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.cut"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditPasteExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.paste"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.find"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindNextExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.find.next"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindPreviousExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.find.prev"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditReplaceExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.replace"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectSaveExecute(TObject *Sender)
{
    theProjectManager.Save();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectCloseExecute(TObject *Sender)
{
    theProjectManager.Close();
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
    ::Messaging::Bus::Publish<Event>(Event("edit.undo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditRedoExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("edit.redo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomInExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("zoom.in"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomOutExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("zoom.out"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomResetExecute(TObject *Sender)
{
    ::Messaging::Bus::Publish<Event>(Event("zoom.reset"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::UpdateProperties(Document* document)
{
    const auto properties = document->GetPropertyInfo();
    for (auto it : properties)
    {
        try
        {
            lmdProperties->RegisterPropCategory(it.second.category, it.first);
        }
        catch(...)
        {
            // ignore exception; since we've already registered this property category and there is no method to test for property registration
        }
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
void __fastcall TfrmIDE::actFileNewAssetExecute(TObject *Sender)
{
    auto dialog = std::unique_ptr<TfrmNewImage>(new TfrmNewImage(this));
    if (dialog->ShowModal() == mrOk)
    {
        auto name = dialog->Name;
        auto width = dialog->Width;
        auto height = dialog->Height;
        theProjectManager.Add("Image", dialog->Type, name, IntToStr(width) + "x" + IntToStr(height));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectOpenExecute(TObject *Sender)
{
    dlgOpen->InitialDir = System::Path::Projects;
    if (dlgOpen->Execute())
    {
        theProjectManager.Open(dlgOpen->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::RefreshMruList()
{
    mnuFileMru->Clear();
    auto name = "mruItem";
    auto i = 831263;
    for (const auto& item : theProjectManager.GetMostRecentlyUsedList())
    {
        auto mi = NewItem(item.Path, 0, false, true, mruOnClick, 0, name+IntToStr(++i));
        mi->OnClick = mruOnClick;
        mnuFileMru->Add(mi);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::mruOnClick(TObject *Sender)
{
    auto mi = dynamic_cast<TMenuItem*>(Sender);
    if (mi)
    {
        auto caption = mi->Caption;
        auto pos = caption.Pos("&");
        if (pos >= 0)
        {
            caption = caption.SubString(0, pos - 1) + caption.SubString(pos + 1, caption.Length());
        }
        theProjectManager.Open(caption);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actNewAssetExecute(TObject *Sender)
{
    if (tvProject->Selected)
    {
        // remove the ending 's' if it exists
        auto type = tvProject->Selected->Text;
        type = type[type.Length()] == 's' ? type.SubString(1, type.Length() - 1) : type;
        theProjectManager.Add("Image", type);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actDeleteAssetExecute(TObject *Sender)
{
    if (tvProject->Selected)
    {
        if (theProjectManager.Remove("Image", tvProject->Selected->Text))
        {
            tvProject->Selected->Delete();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::popProjectPopup(TObject *Sender)
{
    actDeleteAsset->Enabled = false;
    actNewAsset->Enabled = false;
    if (tvProject->Selected && tvProject->Selected->Parent)
    {
        actDeleteAsset->Enabled = !tvProject->Selected->HasChildren;
        actNewAsset->Enabled = tvProject->Selected->Parent->Text == "Images";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actSettingsExecute(TObject *Sender)
{
    auto dialog = std::make_unique<TfrmSettings>(this);
    if (dialog->ShowModal())
    {
    }
}
//---------------------------------------------------------------------------

