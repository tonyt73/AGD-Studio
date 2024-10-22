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
#include "Project/WindowDocument.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmEditorWindow : public TFrame
{
__published:// IDE-managed Components
    TImage *imgView;
    TStatusBar *sbrWindow;
    TActionList *ActionList1;
    TAction *actMoveLeft;
    TAction *actMoveRight;
    TAction *actMoveUp;
    TAction *actMoveDown;
    TAction *actWidthDec;
    TAction *actWidthInc;
    TAction *actHeightDec;
    TAction *actHeightInc;
    void FrameResize(TObject *Sender);
    void imgViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void actMoveLeftExecute(TObject *Sender);
    void actMoveRightExecute(TObject *Sender);
    void actMoveUpExecute(TObject *Sender);
    void actMoveDownExecute(TObject *Sender);
    void actWidthDecExecute(TObject *Sender);
    void actWidthIncExecute(TObject *Sender);
    void actHeightDecExecute(TObject *Sender);
    void actHeightIncExecute(TObject *Sender);
    void FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
private:    // User declarations
    Registrar                   m_Registrar;
    Project::WindowDocument*    m_Document;
    std::unique_ptr<TBitmap>    m_View;
    int                         m_Scalar;

    void             OnEvent(const Event& event);
    bool             IsActive() const;
    void             SetDocument(Project::Document* document);
    void             ShowKeysHelp();
    void             DrawView();

public:        // User declarations
                     TfrmEditorWindow(TComponent* Owner);
                    ~TfrmEditorWindow();

    static  TFrame*  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorWindow(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
