//---------------------------------------------------------------------------
#ifndef fEditorCodeH
#define fEditorCodeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorCode : public TFrame
{
__published:    // IDE-managed Components
    //TBCEditor *BCEditor1;
private:    // User declarations
    Document*                   m_Document;
public:        // User declarations
                    __fastcall  TfrmEditorCode(TComponent* Owner);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorCode(owner);
                                    editor->Document = document;
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property Document*        Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
