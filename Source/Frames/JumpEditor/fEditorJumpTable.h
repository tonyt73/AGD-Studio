//---------------------------------------------------------------------------
#ifndef fEditorJumpTableH
#define fEditorJumpTableH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "LMDDckSite.hpp"
#include "Project/JumpTableDocument.h"
//---------------------------------------------------------------------------
class TfrmEditorJumpTable : public TFrame
{
__published:// IDE-managed Components
    TActionList *ActionList1;
    TAction *actLeft;
    TAction *actRight;
    TAction *actUp;
    TAction *actDown;
    TImage *imgView;
    void __fastcall FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall actLeftExecute(TObject *Sender);
    void __fastcall actRightExecute(TObject *Sender);
    void __fastcall actUpExecute(TObject *Sender);
    void __fastcall actDownExecute(TObject *Sender);
private:    // User declarations
    Project::JumpTableDocument* m_Document;
    std::unique_ptr<TBitmap>    m_View;
    int                         m_ActiveStep;
    int                         m_Scalar;

    void            __fastcall  SetDocument(Project::Document* document);
    bool            __fastcall  IsActive() const;
    void            __fastcall  ShowKeysHelp();
    void            __fastcall  DrawView();

public:        // User declarations
                    __fastcall  TfrmEditorJumpTable(TComponent* Owner);
    static  TFrame* __fastcall  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorJumpTable(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
