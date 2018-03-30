//---------------------------------------------------------------------------
#ifndef fEditorImageH
#define fEditorImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorImage : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TActionList *ActionList1;
    TImageList *ImageList1;
    TAction *actSelectRectangle;
    TAction *actPencil;
    TAction *actBrush;
    TAction *actPaintBucket;
    TAction *actSprayBrush;
    TAction *actStamp;
    TAction *actEraser;
    TAction *actDrawLine;
    TAction *actDrawShape;
    TPopupActionBar *PopupActionBar1;
    TMenuItem *Brush2;
    TMenuItem *DrawLine2;
    TMenuItem *Shapes2;
    TMenuItem *Brush1;
    TMenuItem *PaintBucket1;
    TMenuItem *SprayBrush1;
    TMenuItem *Stamp1;
    TMenuItem *Eraser1;
    TMenuItem *DrawLine1;
    TMenuItem *Shapes1;
    TAction *actGridPixel;
    TAction *actGridCharacter;
    TPanel *Panel3;
    TToolBar *ToolBar3;
    TToolButton *ToolButton13;
    TToolButton *ToolButton14;
    TToolButton *ToolButton15;
    TToolButton *ToolButton16;
    TToolButton *ToolButton17;
    TToolButton *ToolButton18;
    TToolButton *ToolButton19;
    TToolButton *ToolButton20;
    TToolButton *ToolButton21;
    TToolButton *ToolButton22;
    TToolBar *ToolBar4;
    TToolButton *ToolButton23;
    TToolButton *ToolButton24;
    TToolButton *ToolButton25;
    TToolButton *ToolButton26;
    TToolButton *ToolButton27;
    TToolButton *ToolButton28;
    TToolButton *ToolButton29;
    TToolButton *ToolButton30;
    TToolButton *ToolButton31;
    TToolButton *ToolButton32;
    TAction *actText;
    TAction *actDropper;
    TAction *Action3;
    TAction *Action4;
    TAction *Action5;
    TAction *Action6;
    TAction *Action7;
    TAction *Action8;
    TAction *Action9;
    TAction *Action10;
    TAction *Action11;
    TPanel *Panel4;
    TToolButton *ToolButton33;
    TPanel *Panel5;
    TToolBar *ToolBar5;
    TToolButton *ToolButton34;
    TToolButton *ToolButton35;
    TToolButton *ToolButton36;
    TToolButton *ToolButton37;
    TAction *Action12;
    TAction *Action13;
    TAction *Action14;
    TPanel *Panel6;
    TToolBar *ToolBar2;
    TToolButton *ToolButton38;
    TToolButton *ToolButton39;
    TPanel *Panel7;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TAction *Action15;
    TAction *Action16;
    TStatusBar *StatusBar1;
    TPanel *Panel8;
    void __fastcall actSelectRectangleExecute(TObject *Sender);
    void __fastcall actZoomExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actBrushExecute(TObject *Sender);
    void __fastcall actPaintBucketExecute(TObject *Sender);
    void __fastcall actSprayBrushExecute(TObject *Sender);
    void __fastcall actStampExecute(TObject *Sender);
    void __fastcall actEraserExecute(TObject *Sender);
    void __fastcall actDrawLineExecute(TObject *Sender);
    void __fastcall actDrawShapeExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actGridCharacterExecute(TObject *Sender);
    void __fastcall actTextExecute(TObject *Sender);
    void __fastcall actDropperExecute(TObject *Sender);
    void __fastcall Action3Execute(TObject *Sender);
    void __fastcall Action4Execute(TObject *Sender);
    void __fastcall Action5Execute(TObject *Sender);
    void __fastcall Action6Execute(TObject *Sender);
    void __fastcall Action7Execute(TObject *Sender);
    void __fastcall Action8Execute(TObject *Sender);
    void __fastcall Action9Execute(TObject *Sender);
    void __fastcall Action10Execute(TObject *Sender);
    void __fastcall Action11Execute(TObject *Sender);
    void __fastcall Action12Execute(TObject *Sender);
    void __fastcall Action13Execute(TObject *Sender);
    void __fastcall Action14Execute(TObject *Sender);
    void __fastcall Action15Execute(TObject *Sender);
    void __fastcall Action16Execute(TObject *Sender);
    void __fastcall FrameEndDock(TObject *Sender, TObject *Target, int X, int Y);
private:    // User declarations
    Document*                   m_Document;
public:        // User declarations
                    __fastcall  TfrmEditorImage(TComponent* Owner);
                    __fastcall  ~TfrmEditorImage();
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorImage(owner);
                                    editor->Document = document;
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  Document*       Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
