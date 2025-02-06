//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Forms/fAbout.h"
#include "Forms/fNewTileImage.h"
#include "Forms/fSettings.h"
#include "Frames/IDE/fIDE.h"
#include "Frames/Editors/fEditor.h"
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
#pragma link "ElXPThemedControl"
#pragma link "ElTreeInplaceEditors"
#pragma link "ElXTree"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmIDE::TfrmIDE(TComponent* Owner)
: TfrmAppFrame(Owner)
{
    RegisterDocumentEditors();
    m_Registrar.Subscribe<MessageEvent>(_FnBind(TfrmIDE::OnMessageEvent));
    m_Registrar.Subscribe<UpdateProperties>(_FnBind(TfrmIDE::OnUpdateProperties));
    m_Registrar.Subscribe<OpenDocument>(_FnBind(TfrmIDE::OnOpenDocument));
    tvBuild->Items->Clear();
}
//---------------------------------------------------------------------------
__fastcall TfrmIDE::~TfrmIDE()
{
    OnClose();

    m_Registrar.Unsubscribe();

    if (Application && Application->MainForm) {
        Application->MainForm->Menu = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::RegisterDocumentEditors()
{
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(Panel2));
    // map document type (and sub type if required) to an editor
    m_DocumentEditorFactory.Register("Controls"     , &TfrmEditor::Create<TfrmEditorControls>);
    m_DocumentEditorFactory.Register("Jump"         , &TfrmEditor::Create<TfrmEditorJumpTable>);
    m_DocumentEditorFactory.Register("Window"       , &TfrmEditor::Create<TfrmEditorWindow>);
    m_DocumentEditorFactory.Register("Map"          , &TfrmEditor::Create<TfrmEditorMap>);
    m_DocumentEditorFactory.Register("Image"        , &TfrmEditor::Create<TfrmEditorImage>);
    m_DocumentEditorFactory.Register("Text.Messages", &TfrmEditor::Create<TfrmEditorMessages>);
    m_DocumentEditorFactory.Register("Text"         , &TfrmEditor::Create<TfrmEditorCode>);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnActivate(TWinControl* parent)
{
    if (parent != nullptr) {
        Parent = parent;
        Visible = true;
        if (Application && Application->MainForm) {
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
    } else {
        actActions->State = asSuspended;
        Visible = false;
        Parent = nullptr;
    }
    theProjectManager.Initialise(tvProject);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnCreate()
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnMessageEvent(const MessageEvent& message)
{
    if (message.Type < etHelpKeys) {
        if (message.Type == etClear) {
            memMessages->Lines->Clear();
        }
        auto timeStamp = TDateTime::CurrentTime().TimeString();
        const String Types[] = { "Info : ", "Warn : ", "Error: ", "Debug: ", "Info : " };
        memMessages->Lines->Add(timeStamp + " : " + Types[message.Type] + message.Message);
    } else if (message.Type == etHelpKeys) {
        dpEditorKeys->Caption = "HELP FOR " + message.Extra.UpperCase();
        mbKeys->Lines->Clear();
        mbKeys->Lines->Add(message.Message);
        mbKeys->SelLength = 1;
        mbKeys->SelStart = 0;
        mbKeys->SelLength = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnUpdateProperties(const UpdateProperties& event)
{
    assert(event.Id == "update.properties");
    if (tvProject && tvProject && tvProject->Selected) {
        auto doc = reinterpret_cast<Project::Document*>(tvProject->Selected->Tag);
        UpdateDocumentProperties(doc);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnOpenDocument(const OpenDocument& event)
{
    DoOpenDocument(event.Document);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCopyExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.copy"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditCutExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.cut"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditPasteExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.paste"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.find"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindNextExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.find.next"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditFindPreviousExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.find.prev"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditReplaceExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.replace"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectSaveExecute(TObject* /*Sender*/)
{
    theProjectManager.Save();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectCloseExecute(TObject* /*Sender*/)
{
    theProjectManager.Close();
    FOnFormClose(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actHelpAboutExecute(TObject* /*Sender*/)
{
    (new TfrmAbout(this))->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditUndoExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.undo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditRedoExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("edit.redo"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomInExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("zoom.in"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomOutExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("zoom.out"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditZoomResetExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("zoom.reset"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::DoOpenDocument(Project::Document* document)
{
    if (document && document->DockPanel == nullptr) {
        InformationMessage("[IDE] Opening Document: " + document->Name);
        auto dp = new TLMDDockPanel(this);
        auto editor = dynamic_cast<TfrmEditor*>(m_DocumentEditorFactory.Create(document, dp));
        if (editor) {
            dp->Caption = document->Name.UpperCase();
            dp->Tag = reinterpret_cast<NativeInt>(document);
            document->DockPanel = dp;
            editor->OnInitialise();
            UpdateDocumentProperties(document);
            dp->ClientKind = dkDocument;
            dsIDE->DockControl(dp, dsIDE->SpaceZone);
            dp->OnClose = OnDocumentClose;
            dp->Activate();
            dp->Show();
            dp->SetFocus();
            dp->Refresh();
            Bus::Publish<Event>(Event("editor.show"));
        } else {
            ErrorMessage("[IDE] Failed to create editor for Document: " + document->Name);
            delete dp;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::UpdateDocumentProperties(Project::Document* document)
{
    if (document != nullptr) {
        const auto properties = document->GetPropertyInfo();
        for (auto it : properties) {
            auto category = it.second.category + "." + it.first;
            if (m_RegisteredCategories.count(category) == 0) {
                lmdProperties->RegisterPropCategory(it.second.category, it.first);
                m_RegisteredCategories[category] = true;
            }
        }
        lmdProperties->Objects->SetOne(document);
        lmdProperties->ExpandAllCategories();
    } else {
        lmdProperties->Objects->SetOne(nullptr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectExpandAllClick(TObject* /*Sender*/)
{
    tvProject->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectCollapseAllClick(TObject* /*Sender*/)
{
    tvProject->FullCollapse();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectShowLinesClick(TObject* /*Sender*/)
{
    tvProject->ShowLines = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectHideLinesClick(TObject* /*Sender*/)
{
    tvProject->ShowLines = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tbnProjectShowFoldersClick(TObject* /*Sender*/)
{
    tvProject->FullCollapse();
    for (auto node : tvProject->Items) {
        if (node->Level < 2) {
            node->Expand(false);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::lmdPropertiesClick(TObject* /*Sender*/)
{
    if (lmdProperties->Objects->Count >= 1) {
        auto doc = dynamic_cast<Project::Document*>(lmdProperties->Objects->Item[0]);
        if (doc != nullptr && lmdProperties->ActiveItem != nullptr) {
            lblPropertyInfo->Caption = doc->GetPropertyInfo(lmdProperties->ActiveItem->PropName);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectItemSelectedChange(TObject* /*Sender*/, TElXTreeItem *Item)
{
    auto doc = reinterpret_cast<Project::Document*>(Item->Tag);
    if (doc != nullptr) {
        UpdateDocumentProperties(doc);
        auto dockPanel = static_cast<TLMDDockPanel*>(doc->DockPanel);
        if (dockPanel) {
            dockPanel->Activate();
            dockPanel->Show();
            dockPanel->SetFocus();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnDocumentClose(TObject* Sender, TLMDockPanelCloseAction& /*action*/)
{
    auto dockPanel = dynamic_cast<TLMDDockPanel*>(Sender);
    if (dockPanel) {
        auto doc = reinterpret_cast<Project::Document*>(dockPanel->Tag);
        InformationMessage("[IDE] Closing Document: " + doc->Name);
        doc->Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::tvProjectDblClick(TObject* /*Sender*/)
{
    if (tvProject->Selected) {
        auto doc = reinterpret_cast<Project::Document*>(tvProject->Selected->Tag);
        DoOpenDocument(doc);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileProjectOpenExecute(TObject* /*Sender*/)
{
    dlgOpen->InitialDir = Services::Folders::Projects;
    if (dlgOpen->Execute()) {
        theProjectManager.Open(dlgOpen->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::RefreshMruList()
{
    mnuFileMru->Clear();
    auto name = "mruItem";
    auto i = 831263;
    for (const auto& item : theProjectManager.GetMostRecentlyUsedList()) {
        auto mi = NewItem(item.Path, 0, false, true, mruOnClick, 0, name+IntToStr(++i));
        mi->OnClick = mruOnClick;
        mnuFileMru->Add(mi);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::mruOnClick(TObject* Sender)
{
    auto mi = dynamic_cast<TMenuItem*>(Sender);
    if (mi) {
        auto caption = mi->Caption;
        auto pos = caption.Pos("&");
        if (pos >= 0) {
            caption = caption.SubString(0, pos - 1) + caption.SubString(pos + 1, caption.Length());
        }
        theProjectManager.Open(caption);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileNewImageDefaultExecute(TObject* /*Sender*/)
{
    if (tvProject->Selected) {
        // remove the ending 's' if it exists
        auto type = tvProject->Selected->Text;
        type = type[type.Length()] == 's' ? type.SubString(1, type.Length() - 1) : type;
        DoOpenDocument(theProjectManager.Add("Image", type, ""));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileNewTileCustomExecute(TObject* /*Sender*/)
{
    auto dialog = std::unique_ptr<TfrmNewTileImage>(new TfrmNewTileImage(this));
    if (dialog->ShowModal() == mrOk) {
        auto width = dialog->Width;
        auto height = dialog->Height;
        DoOpenDocument(theProjectManager.Add("Image", "Tile", IntToStr(width) + "x" + IntToStr(height)));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actDeleteAssetExecute(TObject* /*Sender*/)
{
    if (tvProject->Selected) {
        auto selected = tvProject->Selected;
        tvProject->Selected = tvProject->Selected->Parent;
        tvProject->Refresh();
        UpdateDocumentProperties(nullptr);
        if (theProjectManager.Remove("Image", selected->Text)) {
            selected->Delete();
        }
     }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::popProjectPopup(TObject* /*Sender*/)
{
    actDeleteAsset->Enabled = false;
    actFileNewImageDefault->Enabled = false;
    actEditDuplicateImage->Enabled = false;
    actEditSplitIntoTiles->Enabled = false;
    if (tvProject->Selected && tvProject->Selected->Parent) {
        actDeleteAsset->Enabled = !tvProject->Selected->HasChildren && tvProject->Selected->Parent->Parent->Text == "Images";
        actEditDuplicateImage->Enabled = !tvProject->Selected->HasChildren && tvProject->Selected->Parent->Parent->Text == "Images";
        actFileNewImageDefault->Enabled = tvProject->Selected->Parent->Text == "Images";

        auto type = tvProject->Selected->Parent->Text;
        if (type == "Tiles") {
            type = type[type.Length()] == 's' ? type.SubString(1, type.Length() - 1) : type;
            auto doc = dynamic_cast<Project::ImageDocument*>(theDocumentManager.Get("Image", type, tvProject->Selected->Text));
            actEditSplitIntoTiles->Enabled = (doc != nullptr && doc->ImagesPerFrame > 1);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::popProjectClose(TObject* /*Sender*/)
{
    actDeleteAsset->Enabled = true;
    actFileNewImageDefault->Enabled = true;
    actEditDuplicateImage->Enabled = true;
    actEditSplitIntoTiles->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actSettingsExecute(TObject* /*Sender*/)
{
    std::make_unique<TfrmSettings>(this)->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditorHelpExecute(TObject* /*Sender*/)
{
    Bus::Publish<Event>(Event("editor.help"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewBuildResultsExecute(TObject* /*Sender*/)
{
    dpBuild->PanelVisible = actViewBuildResults->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewSearchResultsExecute(TObject* /*Sender*/)
{
    dpSearchResults->PanelVisible = actViewSearchResults->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewTodoExecute(TObject* /*Sender*/)
{
    dpTodo->PanelVisible = actViewTodo->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewEditorKeysExecute(TObject* /*Sender*/)
{
    dpEditorKeys->PanelVisible = actViewEditorKeys->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actViewMessagesExecute(TObject* /*Sender*/)
{
    dpMessages->PanelVisible = actViewMessages->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actGameRunExecute(TObject* /*Sender*/)
{
    m_Builder.Execute();
    dpBuild->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::OnClose()
{
    theProjectManager.Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::dsIDEChange(TObject* Sender)
{
    auto ds = dynamic_cast<TLMDDockSite*>(Sender);
    if (ds) {
        Bus::Publish<Event>(Event("editor.help"));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileNewTileExecute(TObject* /*Sender*/)
{
    auto doc = theProjectManager.Add("Image", "Tile", "");
    DoOpenDocument(doc);
    UpdateDocumentProperties(doc);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileNewObjectExecute(TObject* /*Sender*/)
{
    auto doc = theProjectManager.Add("Image", "Object", "");
    DoOpenDocument(doc);
    UpdateDocumentProperties(doc);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actFileNewSpriteExecute(TObject* /*Sender*/)
{
    auto doc = theProjectManager.Add("Image", "Sprite", "");
    DoOpenDocument(doc);
    UpdateDocumentProperties(doc);
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditDuplicateImageExecute(TObject* /*Sender*/)
{
    if (tvProject->Selected) {
        auto type = tvProject->Selected->Parent->Text;
        type = type[type.Length()] == 's' ? type.SubString(1, type.Length() - 1) : type;
        auto newDoc = theProjectManager.Add("Image", type, "");
        auto oldDoc = theDocumentManager.Get("Image", type, tvProject->Selected->Text);
        InformationMessage("[IDE] Duplicating Document: " + oldDoc->Name + " into " + newDoc->Name);
        newDoc->Copy(oldDoc);
        DoOpenDocument(newDoc);
        tvProject->Refresh();
        UpdateDocumentProperties(newDoc);
     }
}
//---------------------------------------------------------------------------
void __fastcall TfrmIDE::actEditSplitIntoTilesExecute(TObject* /*Sender*/)
{
    if (tvProject->Selected) {
        // close the document

        // split it into singles

        // update the map

        // remove the original doc
    }
}
//---------------------------------------------------------------------------

