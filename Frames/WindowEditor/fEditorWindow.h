//---------------------------------------------------------------------------
#ifndef fEditorWindowH
#define fEditorWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorWindow : public TFrame
{
__published:// IDE-managed Components
private:    // User declarations
    Document*                   m_Document;
public:        // User declarations
                    __fastcall  TfrmEditorWindow(TComponent* Owner);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorWindow(owner);
                                    editor->Document = document;
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  Document*       Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
