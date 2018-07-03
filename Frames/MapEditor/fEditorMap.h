//---------------------------------------------------------------------------
#ifndef fEditorMapH
#define fEditorMapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class TfrmEditorMap : public TFrame
{
__published:    // IDE-managed Components
    TPanel *panToolbar;
    TLabel *Label1;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnShape;
    TPanel *panSplitter1;
    TPanel *panSplitter3;
    TPanel *panSplitter4;
    TToolBar *tbrGrids;
    TToolButton *btnGridCharacter;
    TToolButton *btnGridPixel;
    TImageList *tbrImagesEnabled;
    TImageList *tbrImagesDisabled;
    TActionList *tbrActions;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actLine;
    TAction *actShape;
    TAction *actGridPixel;
    TAction *actGridCharacter;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TAction *actUndo;
    TAction *actRedo;
    TPanel *panEditorContainer;
    TPanel *panViewFrame;
    TImage *imgEditor;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actGridCharacterExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
private:    // User declarations
    Document*                   m_Document;
public:        // User declarations
                    __fastcall  TfrmEditorMap(TComponent* Owner);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorMap(owner);
                                    editor->Document = document;
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  Document*       Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
