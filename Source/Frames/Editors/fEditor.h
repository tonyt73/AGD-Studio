//---------------------------------------------------------------------------
#ifndef fEditorH
#define fEditorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
class TfrmEditor : public TFrame
{
__published:    // IDE-managed Components
    void __fastcall FrameEnter(TObject *Sender);

private:        // User declarations
    void            __fastcall  ShowKeysHelp();

protected:      // User declarations
    ::Messaging::Registrar      m_Registrar;
    Project::Document*          m_Document;
    String                      m_Name;
    String                      m_KeysHelp;

    void            __fastcall  SetDocument(Project::Document* document);

public:         // User declarations
                    __fastcall  TfrmEditor(TComponent* Owner, const String& Name);
                    __fastcall ~TfrmEditor();

            bool    __fastcall  IsActive() const;
    virtual void    __fastcall  OnEvent(const Event& event);
};
//---------------------------------------------------------------------------
#endif
