//---------------------------------------------------------------------------
#ifndef fEditorMessagesH
#define fEditorMessagesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "fEditorCode.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/Document.h"
#include "Project/Documents/Text.h"
#include "Project/Documents/CharacterSet.h"
#include "Visuals/Image.h"
#include "Visuals/GraphicsMode.h"
#include "fMultiImageView.h"
//---------------------------------------------------------------------------
class TfrmEditorMessages : public TfrmEditor
{
__published:// IDE-managed Components
    TImage *imgView;
    TMultiImageViewFrame *fFramesView;
    TPanel *panCharacterSet;
    TPanel *panContainer;
    TPanel *Panel1;
    TPanel *Panel2;
    TfrmEditorCode *ecMessageEditor;
    TScrollBox *sbxView;
    TSplitter *Splitter1;
    TTimer *tmrRefreshView;
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall OnStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges);
    void __fastcall sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall tmrRefreshViewTimer(TObject *Sender);

private:    // User declarations
    Project::CharacterSetDocument*  m_CharacterSet;     // the character set document
    Visuals::ImageList              m_Frames;           // the image documents frames as bitmap images
    const Visuals::GraphicsMode&    m_GraphicsMode;     // the graphics mode used by the project
    bool                            m_RefreshView;      // get the timer function to refresh the view
    std::unique_ptr<TImage>         m_Tile;

    void                __fastcall  OnDocumentSet();
    bool                __fastcall  IsActive() const;
    void                __fastcall  RefreshView();
    void                __fastcall  RefreshCharacterSet();

public:     // User declarations
                        __fastcall  TfrmEditorMessages(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditorMessages *frmEditorMessages;
//---------------------------------------------------------------------------
#endif
