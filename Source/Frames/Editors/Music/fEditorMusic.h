//---------------------------------------------------------------------------
#ifndef fEditorMusicH
#define fEditorMusicH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorMusic : public TfrmEditor
{
__published:    // IDE-managed Components
private:        // User declarations
public:         // User declarations
                    __fastcall  TfrmEditorMusic(TComponent* Owner);

    static  TFrame* __fastcall  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorMusic(owner);
                                    editor->Document = document;
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

  __property Project::Document* Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
