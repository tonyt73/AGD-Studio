//---------------------------------------------------------------------------
#ifndef fEditorMessagesH
#define fEditorMessagesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Project/Document.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "LMDDckSite.hpp"
#include "Project/TextDocuments.h"
//---------------------------------------------------------------------------
class TfrmEditorMessages : public TFrame
{
__published:// IDE-managed Components
    TPanel *panCharacterSet;
    TPanel *panContainer;
    TPanel *Panel1;
    TPanel *Panel2;
    TSplitter *Splitter1;
    void __fastcall FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
private:    // User declarations
    MessageDocument*            m_Document;
    std::unique_ptr<TBitmap>    m_View;

    void            __fastcall  SetDocument(Document* document);
    bool            __fastcall  IsActive() const;
    void            __fastcall  ShowKeysHelp();

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
