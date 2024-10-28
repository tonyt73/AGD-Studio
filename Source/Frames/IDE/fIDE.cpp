//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "Forms/fAbout.h"
#include "Forms/fNewImage.h"
#include "Forms/fSettings.h"
#include "Frames/IDE/fIDE.h"
#include "Frames/Editors/Code/fEditorCode.h"
#include "Frames/Editors/Controls/fEditorControls.h"
#include "Frames/Editors/Images/fEditorImage.h"
#include "Frames/Editors/JumpTable/fEditorJumpTable.h"
#include "Frames/Editors/Map/fEditorMap.h"
#include "Frames/Editors/Messages/fEditorMessages.h"
#include "Frames/Editors/Window/fEditorWindow.h"
#include "Project/ProjectManager.h"
#include "Settings/ThemeManager.h"
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
    m_Registrar.Subscribe<MessageEvent>(OnMessageEvent);
    m_Registrar.Subscribe<UpdateProperties>(OnUpdateProperties);
    tvBuild->Items->Clear();
}
//---------------------------------------------------------------------------
__fastcall TfrmIDE::~TfrmIDE()
{
    OnClose();

    m_Registrar.Unsubscribe();

    if (Application && Application->MainForm)
    {
        Application->MainForm->Menu = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::RegisterDocumentEditors()
{
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(Panel2));
    // map document type (and sub type if required) to an editor
    m_DocumentEditorFactory.Register("Controls"     , &TfrmEditorControls::Create);
    m_DocumentEditorFactory.Register("Jump"         , &TfrmEditorJumpTable::Create);
    m_DocumentEditorFactory.Register("Window"       , &TfrmEditorWindow::Create);
    m_DocumentEditorFactory.Register("Map"          , &TfrmEditorMap::Create);
    m_DocumentEditorFactory.Register("Image"        , &TfrmEditorImage::Create);
    m_DocumentEditorFactory.Register("Text.Messages", &TfrmEditorMessages::Create);
    m_DocumentEditorFactory.Register("Text"         , &TfrmEditorCode::Create);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnActivate(TWinControl* parent)
{
    if (parent != nullptr)
    {
        Parent = parent;
        Visible = true;
        if (Application && Application->MainForm)
        {
            Application->MainForm->Menu = mnuMain;
            Application->MainForm->Caption = ApplicationName;
        }
        ThemeManager::ReapplyStyle();
        Color = ThemeManager::Background;
        tvProject->BackGroundColor = ThemeManager::Background;
        tvBuild->BackGroundColor = ThemeManager::Background;
        m_Builder.TreeView = tvBuild;
        dsIDE->Invalidate();
        RefreshMruList();
        actActions->State = asNormal;
    }
    else
    {
        actActions->State = asSuspended;
        Visible = false;
        Parent = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnMessageEvent(const MessageEvent& message)
{
    if (message.Type < etHelpKeys)
    {
        if (message.Type == etClear)
        {
            memMessages->Lines->Clear();
        }
        auto timeStamp = TDateTime::CurrentTime().TimeString();
        const String Types[] = { "Info : ", "Warn : ", "Error: ", "Debug: ", "Info : " };
        memMessages->Lines->Add(timeStamp + " : " + Types[message.Type] + message.Message);
    }
    else if (message.Type == etHelpKeys)
    {
        mbKeys->Lines->Clear();
        mbKeys->Lines->Add(message.Message);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnUpdateProperties(const UpdateProperties& event)
{
    if (event.Id == "update.properties")
    {
        auto doc = (Project::Document*)((NativeInt)tvProject->Selected->Tag);
        UpdateDocumentProperties(doc);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCopyExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.copy"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCutExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.cut"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditPasteExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.paste"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.find"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindNextExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.find.next"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindPreviousExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.find.prev"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditReplaceExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.replace"));
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
    Bus::Publish<Event>(Event("edit.undo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditRedoExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("edit.redo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomInExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("zoom.in"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomOutExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("zoom.out"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomResetExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("zoom.reset"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::UpdateDocumentProperties(Project::Document* document)
{
    if (document != nullptr)
    {
        const auto properties = document->GetPropertyInfo();
        for (auto it : properties)
        {
            auto category = it.second.category + "." + it.first;
            if (m_RegisteredCategories.count(category) == 0)
            {
                lmdProperties->RegisterPropCategory(it.second.category, it.first);
                m_RegisteredCategories[category] = true;
            }
        }
        lmdProperties->Objects->SetOne(document);
        lmdProperties->ExpandAllCategories();
    }
    else
    {
        lmdProperties->Objects->SetOne(nullptr);
    }
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
        auto doc = dynamic_cast<Project::Document*>(lmdProperties->Objects->Item[0]);
        if (doc != nullptr && lmdProperties->ActiveItem != nullptr)
        {
            lblPropertyInfo->Caption = doc->GetPropertyInfo(lmdProperties->ActiveItem->PropName);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectItemSelectedChange(TObject *Sender, TElXTreeItem *Item)
{
    auto doc = reinterpret_cast<Project::Document*>((TObject*)Item->Tag);
    if (doc != nullptr)
    {
        UpdateDocumentProperties(doc);
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
        auto doc = (Project::Document*)dockPanel->Tag;
        InformationMessage("[IDE] Closing Document: " + doc->Name);
        doc->Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectDblClick(TObject *Sender)
{
    if (tvProject->Selected)
    {
        auto doc = (Project::Document*)((NativeInt)tvProject->Selected->Tag);
        if (doc && doc->DockPanel == nullptr)
        {
            InformationMessage("[IDE] Opening Document: " + doc->Name);
            auto dp = new TLMDDockPanel(this);
            if (m_DocumentEditorFactory.Create(doc, dp))
            {
                dp->Caption = doc->Name.UpperCase();
                dp->Tag = (NativeInt)doc;
                doc->DockPanel = dp;
                UpdateDocumentProperties(doc);
                dp->ClientKind = dkDocument;
                dsIDE->DockControl(dp, dsIDE->SpaceZone);
                dp->OnClose = OnDocumentClose;
                dp->Activate();
                dp->Show();
                dp->SetFocus();
                dp->Refresh();
                Bus::Publish<Event>(Event("editor.show"));
            }
            else
            {
                ErrorMessage("[IDE] Failed to create editor for Document: " + doc->Name);
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
        auto width = dialog->Width;
        auto height = dialog->Height;
        theProjectManager.Add("Image", dialog->Type, IntToStr(width) + "x" + IntToStr(height));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectOpenExecute(TObject *Sender)
{
    dlgOpen->InitialDir = Services::Folders::Projects;
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
        theProjectManager.Add("Image", type, "");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actDeleteAssetExecute(TObject *Sender)
{
    if (tvProject->Selected)
    {
        auto selected = tvProject->Selected;
        tvProject->Selected = tvProject->Selected->Parent;
        tvProject->Refresh();
        UpdateDocumentProperties(nullptr);
        if (theProjectManager.Remove("Image", selected->Text))
        {
            selected->Delete();
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
        actDeleteAsset->Enabled = !tvProject->Selected->HasChildren && tvProject->Selected->Parent->Parent->Text == "Images";
        actNewAsset->Enabled = tvProject->Selected->Parent->Text == "Images";
        btnNewImageCustom->Enabled = tvProject->Selected->Parent->Text == "Images" || tvProject->Selected->Text == "Images";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actSettingsExecute(TObject *Sender)
{
    std::make_unique<TfrmSettings>(this)->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditorHelpExecute(TObject *Sender)
{
    Bus::Publish<Event>(Event("editor.help"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewBuildResultsExecute(TObject *Sender)
{
    dpBuild->PanelVisible = actViewBuildResults->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewSearchResultsExecute(TObject *Sender)
{
    dpSearchResults->PanelVisible = actViewSearchResults->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewTodoExecute(TObject *Sender)
{
    dpTodo->PanelVisible = actViewTodo->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewEditorKeysExecute(TObject *Sender)
{
    dpEditorKeys->PanelVisible = actViewEditorKeys->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewMessagesExecute(TObject *Sender)
{
    dpMessages->PanelVisible = actViewMessages->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actGameRunExecute(TObject *Sender)
{
    m_Builder.Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnClose()
{
    theProjectManager.Close();
}
//---------------------------------------------------------------------------

