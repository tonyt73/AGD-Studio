//---------------------------------------------------------------------------
#ifndef fEditorMessagesH
#define fEditorMessagesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
#include "Visuals/Image.h"
#include "Visuals/GraphicsMode.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/TextDocuments.h"
#include "Project/CharacterSetDocument.h"
#include "..\CodeEditor\fEditorCode.h"
#include "..\ImageEditor\fMultiImageView.h"
//---------------------------------------------------------------------------
class TfrmEditorMessages : public TFrame
{
__published:// IDE-managed Components
    TPanel *panCharacterSet;
    TPanel *panContainer;
    TPanel *Panel1;
    TPanel *Panel2;
    TSplitter *Splitter1;
    TfrmEditorCode *ecMessageEditor;
    TMultiImageViewFrame *fFramesView;
    TScrollBox *sbxView;
    TImage *imgView;
    TTimer *tmrRefreshView;
    void __fastcall FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall OnStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges);
    void __fastcall tmrRefreshViewTimer(TObject *Sender);
    void __fastcall sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
private:    // User declarations
    Project::Document*             m_Document;         // the messages document
    Project::CharacterSetDocument* m_CharacterSet;     // the character set document
    Visuals::ImageList              m_Frames;           // the image documents frames as bitmap images
    const Visuals::GraphicsMode&    m_GraphicsMode;     // the graphics mode used by the project
    bool                            m_RefreshView;      // get the timer function to refresh the view
    std::unique_ptr<TImage>         m_Tile;

    void                __fastcall  SetDocument(Project::Document* document);
    bool                __fastcall  IsActive() const;
    void                __fastcall  RefreshView();
    void                __fastcall  RefreshCharacterSet();

public:     // User declarations
                        __fastcall  TfrmEditorMessages(TComponent* Owner);
    static  TFrame*     __fastcall  Create(Project::Document* document, TComponent* owner)
                                    {
                                        auto editor = new TfrmEditorMessages(owner);
                                        editor->SetDocument(document);
                                        document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                        return editor;
                                    }
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditorMessages *frmEditorMessages;
//---------------------------------------------------------------------------
#endif
