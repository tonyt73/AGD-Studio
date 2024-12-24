//---------------------------------------------------------------------------
#ifndef fEditorH
#define fEditorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
class TfrmEditor : public TFrame
{
__published:    // IDE-managed Components
    void            __fastcall  FrameEnter(TObject *Sender);

private:        // User declarations
    void            __fastcall  ShowKeysHelp();
    void            __fastcall  SetDocument(Project::Document* document);

protected:      // User declarations
    Registrar                   m_Registrar;
    Project::Document*          m_Document;
    String                      m_Name;
    String                      m_KeysHelp;

    virtual void    __fastcall  OnDocumentSet();

public:         // User declarations
                    __fastcall  TfrmEditor(TComponent* Owner, const String& Name);
                    __fastcall ~TfrmEditor() override;

    template <class T>
    static  TFrame* __fastcall  Create(Project::Document* document, TComponent* owner) {
                                    auto editor = new T(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

            bool    __fastcall  IsActive() const;
    virtual void    __fastcall  OnEvent(const Event& event);
    virtual void    __fastcall  OnInitialise();

  __property Project::Document* Document = { read = m_Document, write = SetDocument };
};
//---------------------------------------------------------------------------
#endif
