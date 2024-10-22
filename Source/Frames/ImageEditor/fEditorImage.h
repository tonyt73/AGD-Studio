//---------------------------------------------------------------------------
#ifndef fEditorImageH
#define fEditorImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include "LMDDckSite.hpp"
#include "Project/ImageDocument.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Visuals/Image.h"
#include "Visuals/GraphicsMode.h"
#include "Frames/ImageEditor/CanvasTool.h"
#include "Frames/ImageEditor/BlockTypeTool.h"
#include "Frames/WndProcHandlers.h"
#include "fBlockTypes.h"
#include "fMultiImageView.h"
#include "fPaletteAttribute.h"
#include "fPaletteBitmap.h"
#include "fToolbar.h"
#include "fToolbarShape.h"
#include "fULAplusBitmap.h"
#include "fPaletteMonoAttribute.h"
//---------------------------------------------------------------------------
class TfrmEditorImage : public TFrame
{
__published:    // IDE-managed Components
    TPanel *panToolOptions;
    TActionList *tbrActions;
    TImageList *tbrImagesEnabled;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actFill;
    TAction *actSprayBrush;
    TAction *actEraser;
    TAction *actLine;
    TAction *actShape;
    TPopupActionBar *popTools;
    TMenuItem *mnuSelect;
    TMenuItem *mnuText;
    TMenuItem *mnuBrush;
    TMenuItem *mnuLine;
    TMenuItem *mnuShapes;
    TMenuItem *mnuDropper;
    TMenuItem *mnuSprayBrush;
    TMenuItem *mnuFill;
    TAction *actGridPixel;
    TAction *actGridCharacter;
    TAction *actText;
    TAction *actDropper;
    TStatusBar *barStatus;
    TAction *actRotateLeft;
    TAction *actRotateRight;
    TAction *actRotateUp;
    TAction *actRotateDown;
    TAction *actFlipVertical;
    TAction *actFlipHorizontal;
    TAction *actRotateLeft90;
    TAction *actRotateRight90;
    TAction *actMonoOn;
    TAction *actMonoOff;
    TScrollBox *sbxView;
    TAction *actBrush;
    TMenuItem *mnuEraser;
    TButton *btnTool;
    TPanel *panEditorContainer;
    TPanel *panViewFrame;
    TImage *imgEditor;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TPanel *panContainer;
    TPanel *panFrameView;
    TPopupMenu *popFrames;
    TMenuItem *popAddFrame;
    TMenuItem *popInsertFrame;
    TMenuItem *popRemoveFrame;
    TAction *actAnimatePlay;
    TAction *actAnimateStop;
    TAction *actToggleAnimation;
    TTimer *tmrAnimate;
    TAction *actUndo;
    TAction *actRedo;
    TPanel *Panel2;
    TfrmToolbarShape *toolbarShape;
    TMenuItem *mnuPencil;
    TPanel *panToolbar;
    TToolBar *tbrShiftRotates;
    TToolButton *btnRotateLeft;
    TToolButton *btnRotateRight;
    TToolButton *btnRotateDown;
    TToolButton *btnRotateUp;
    TToolButton *btnFlipHorizontal;
    TToolButton *btnFlipVertical;
    TToolButton *btnRotateLeft90;
    TToolButton *btnRotateRight90;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnText;
    TToolButton *btnPencil;
    TToolButton *btnBrush;
    TToolButton *btnLine;
    TToolButton *btnShape;
    TToolButton *btnSprayBrush;
    TToolButton *btnFill;
    TPanel *panSplitter1;
    TPanel *panGrids;
    TPanel *panColour;
    TToolBar *tbrMono;
    TToolButton *btnMonoOff;
    TToolButton *btnMonoOn;
    TPanel *panAnimation;
    TToolBar *tbrGrids;
    TToolButton *btnGridCharacter;
    TToolButton *btnGridPixel;
    TToolBar *tbrAnimate;
    TToolButton *btnAnimatePlay;
    TToolButton *btnAnimateStop;
    TPanel *Panel1;
    TLabel *lblTools;
    TLabel *Label2;
    TPanel *Panel3;
    TMultiImageViewFrame *fFrameView;
    TfrmPaletteAttribute *palAttribute;
    TfrmPaletteBitmap *palBitmap;
    TfrmULAplusBitmap *palULAPlus;
    TToolBar *tbrBlockType;
    TToolButton *btnModePaint;
    TToolButton *btnModeBlock;
    TAction *actModePaint;
    TAction *actModeBlock;
    TfrmBlockTypes *palBlocks;
    TImageList *tbrImagesDisabled;
    TPanel *panModes;
    TfrmPaletteMonoAttribute *palMonoAttribute;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actBrushExecute(TObject *Sender);
    void __fastcall actFillExecute(TObject *Sender);
    void __fastcall actSprayBrushExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actTextExecute(TObject *Sender);
    void __fastcall FrameEndDock(TObject *Sender, TObject *Target, int X, int Y);
    void __fastcall actRotateLeftExecute(TObject *Sender);
    void __fastcall actRotateRightExecute(TObject *Sender);
    void __fastcall actRotateUpExecute(TObject *Sender);
    void __fastcall actRotateDownExecute(TObject *Sender);
    void __fastcall actFlipVerticalExecute(TObject *Sender);
    void __fastcall actFlipHorizontalExecute(TObject *Sender);
    void __fastcall actRotateLeft90Execute(TObject *Sender);
    void __fastcall actRotateRight90Execute(TObject *Sender);
    void __fastcall actMonoOnExecute(TObject *Sender);
    void __fastcall actMonoOffExecute(TObject *Sender);
    void __fastcall panEditorContainerClick(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall sbxViewResize(TObject *Sender);
    void __fastcall sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall popAddFrameClick(TObject *Sender);
    void __fastcall popInsertFrameClick(TObject *Sender);
    void __fastcall popRemoveFrameClick(TObject *Sender);
    void __fastcall actAnimatePlayExecute(TObject *Sender);
    void __fastcall actAnimateStopExecute(TObject *Sender);
    void __fastcall actToggleAnimationExecute(TObject *Sender);
    void __fastcall tmrAnimateTimer(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall imgEditorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall actModePaintExecute(TObject *Sender);
    void __fastcall actModeBlockExecute(TObject *Sender);
    void __fastcall imgEditorMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);

private:    // User declarations
    typedef std::map<int, std::unique_ptr<CanvasTool>> CanvasToolMap;

    ::Messaging::Registrar      m_Registrar;
    EraseHandler                m_EraseHandlerView;

    Project::ImageDocument*     m_ImageDocument;    // the image document we are editing
    Visuals::ImageList          m_Frames;           // the image documents frames as bitmap images
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    float                       m_Magnification;    // the magnification of the main view
    int                         m_SelectedFrame;    // the frame we are editing
    CanvasToolMap               m_CanvasToolMap;    // a map to all the canvas paint tools
    int                         m_CanvasTool;       // the selected canvas paint tool
    TfrmToolbar*                m_Toolbar;          // the current tools toolbar
   const Visuals::GraphicsMode& m_GraphicsMode;     // the graphics mode used by the project
    bool                        m_GridPixel;
    bool                        m_GridBlock;
    BlockTypeTool               m_BlockTypeTool;
    String                      m_LastModeString;   //

    void            __fastcall  SetDocument(Project::Document* document);
    void            __fastcall  OnEvent(const Event& event);
    bool            __fastcall  IsActive() const;
    void            __fastcall  DrawGrids();
    void            __fastcall  RefreshView(bool redraw = false);
    void            __fastcall  RefreshFramesView();
    void            __fastcall  OnFrameSelected(TObject *Sender);
    TPoint          __fastcall  ToImagePt(int X, int Y);
    void            __fastcall  SetCanvasColors();
    void            __fastcall  ChangeToolbar(TfrmToolbar* toolbar);
    void            __fastcall  ShowKeysHelp();

public:        // User declarations
                    __fastcall  TfrmEditorImage(TComponent* Owner);
                    __fastcall ~TfrmEditorImage();

     static  TFrame* __fastcall Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorImage(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  Project::ImageDocument*  Image = { read = m_ImageDocument, write = m_ImageDocument };
};
//---------------------------------------------------------------------------
#endif
