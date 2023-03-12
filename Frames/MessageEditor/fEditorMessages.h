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
#include "Graphics/Image.h"
#include "Graphics/GraphicsMode.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/TextDocuments.h"
#include "Project/CharacterSetDocument.h"
#include "fEditorCode.h"
#include "fMultiImageView.h"
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
    void __fastcall FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
private:    // User declarations
    Document*                   m_Document;
    Agdx::ImageList             m_Frames;           // the image documents frames as bitmap images
    const Agdx::GraphicsMode&   m_GraphicsMode;     // the graphics mode used by the project


    void            __fastcall  SetDocument(Document* document);
    bool            __fastcall  IsActive() const;

public:     // User declarations
                    __fastcall  TfrmEditorMessages(TComponent* Owner);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
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
