//---------------------------------------------------------------------------
#ifndef fEditorWindowH
#define fEditorWindowH
//---------------------------------------------------------------------------
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "Project/WindowDocument.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmEditorWindow : public TfrmEditor
{
__published:    // IDE-managed Components
    TAction *actHeightDec;
    TAction *actHeightInc;
    TAction *actMoveDown;
    TAction *actMoveLeft;
    TAction *actMoveRight;
    TAction *actMoveUp;
    TActionList *actList;
    TImage *imgView;
    TStatusBar *sbrWindow;
    void __fastcall actHeightDecExecute(TObject *Sender);
    void __fastcall actHeightIncExecute(TObject *Sender);
    void __fastcall actMoveDownExecute(TObject *Sender);
    void __fastcall actMoveLeftExecute(TObject *Sender);
    void __fastcall actMoveRightExecute(TObject *Sender);
    void __fastcall actMoveUpExecute(TObject *Sender);
    void __fastcall actWidthDecExecute(TObject *Sender);
    void __fastcall actWidthIncExecute(TObject *Sender);
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall imgViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private:    // User declarations
    std::unique_ptr<TBitmap>    m_View;
    int                         m_Scalar;

    void            __fastcall  DrawView();

public:        // User declarations
                    __fastcall  TfrmEditorWindow(TComponent* Owner);

    static  TFrame* __fastcall  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorWindow(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
