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
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "Project/Documents/JumpTable.h"
//---------------------------------------------------------------------------
class TfrmEditorJumpTable : public TfrmEditor
{
__published:// IDE-managed Components
    TAction *actDown;
    TAction *actLeft;
    TAction *actRight;
    TAction *actUp;
    TActionList *ActionList1;
    TImage *imgView;
    void __fastcall actDownExecute(TObject *Sender);
    void __fastcall actLeftExecute(TObject *Sender);
    void __fastcall actRightExecute(TObject *Sender);
    void __fastcall actUpExecute(TObject *Sender);
    void __fastcall FrameResize(TObject *Sender);

private:    // User declarations
    std::unique_ptr<TBitmap>    m_View;
    int                         m_ActiveStep;
    int                         m_Scalar;

    void            __fastcall  DrawView();

public:     // User declarations
                    __fastcall  TfrmEditorJumpTable(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
#endif
