//---------------------------------------------------------------------------
#ifndef fEditorMusicH
#define fEditorMusicH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorMusic : public TFrame
{
__published:    // IDE-managed Components
private:    // User declarations
    Project::Document*          m_Document;
public:        // User declarations
                     TfrmEditorMusic(TComponent* Owner);
    static  TFrame*  Create(Project::Document* document, TComponent* owner)
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
