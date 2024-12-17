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
//---------------------------------------------------------------------------
#include "../../WndProcHandlers.h"
#include "fEditor.h"
#include "CanvasTool.h"
#include "BlockTypeTool.h"
#include "fBlockTypes.h"
#include "fMultiImageView.h"
#include "fPaletteBitmap.h"
#include "fPaletteAttribute.h"
#include "fPaletteMonoAttribute.h"
#include "fToolbar.h"
#include "fToolbarShape.h"
#include "fULAplusBitmap.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/BaseImage.h"
#include "Visuals/Image.h"
#include "Visuals/GraphicsMode.h"
//---------------------------------------------------------------------------
class TfrmEditorImage : public TfrmEditor
{
__published:    // IDE-managed Components
    TAction *actAnimatePlay;
    TAction *actAnimateStop;
    TAction *actBrush;
    TAction *actDropper;
    TAction *actEraser;
    TAction *actFill;
    TAction *actFlipHorizontal;
    TAction *actFlipVertical;
    TAction *actGridCharacter;
    TAction *actGridPixel;
    TAction *actLine;
    TAction *actModeBlock;
    TAction *actModePaint;
    TAction *actMonoOff;
    TAction *actMonoOn;
    TAction *actPencil;
    TAction *actRedo;
    TAction *actRotateDown;
    TAction *actRotateLeft;
    TAction *actRotateLeft90;
    TAction *actRotateRight;
    TAction *actRotateRight90;
    TAction *actRotateUp;
    TAction *actSelect;
    TAction *actShape;
    TAction *actSprayBrush;
    TAction *actText;
    TAction *actToggleAnimation;
    TAction *actUndo;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TActionList *tbrActions;
    TButton *btnTool;
    TfrmBlockTypes *palBlocks;
    TfrmPaletteAttribute *palAttribute;
    TfrmPaletteBitmap *palBitmap;
    TfrmPaletteMonoAttribute *palMonoAttribute;
    TfrmToolbarShape *toolbarShape;
    TfrmULAplusBitmap *palULAPlus;
    TImage *imgEditor;
    TImageList *tbrImagesDisabled;
    TImageList *tbrImagesEnabled;
    TLabel *Label2;
    TLabel *lblTools;
    TMenuItem *mnuBrush;
    TMenuItem *mnuDropper;
    TMenuItem *mnuEraser;
    TMenuItem *mnuFill;
    TMenuItem *mnuLine;
    TMenuItem *mnuPencil;
    TMenuItem *mnuSelect;
    TMenuItem *mnuShapes;
    TMenuItem *mnuSprayBrush;
    TMenuItem *mnuText;
    TMenuItem *popAddFrame;
    TMenuItem *popInsertFrame;
    TMenuItem *popRemoveFrame;
    TMultiImageViewFrame *fFrameView;
    TPanel *panAnimation;
    TPanel *panColour;
    TPanel *panContainer;
    TPanel *panEditorContainer;
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *panFrameView;
    TPanel *panGrids;
    TPanel *panModes;
    TPanel *panSplitter1;
    TPanel *panToolbar;
    TPanel *panToolOptions;
    TPanel *panViewFrame;
    TPopupActionBar *popTools;
    TPopupMenu *popFrames;
    TScrollBox *sbxView;
    TStatusBar *barStatus;
    TTimer *tmrAnimate;
    TToolBar *tbrAnimate;
    TToolBar *tbrBlockType;
    TToolBar *tbrGrids;
    TToolBar *tbrMono;
    TToolBar *tbrShiftRotates;
    TToolBar *tbrTools;
    TToolButton *btnAnimatePlay;
    TToolButton *btnAnimateStop;
    TToolButton *btnBrush;
    TToolButton *btnFill;
    TToolButton *btnFlipHorizontal;
    TToolButton *btnFlipVertical;
    TToolButton *btnGridCharacter;
    TToolButton *btnGridPixel;
    TToolButton *btnLine;
    TToolButton *btnModeBlock;
    TToolButton *btnModePaint;
    TToolButton *btnMonoOff;
    TToolButton *btnMonoOn;
    TToolButton *btnPencil;
    TToolButton *btnRotateDown;
    TToolButton *btnRotateLeft;
    TToolButton *btnRotateLeft90;
    TToolButton *btnRotateRight;
    TToolButton *btnRotateRight90;
    TToolButton *btnRotateUp;
    TToolButton *btnSelect;
    TToolButton *btnShape;
    TToolButton *btnSprayBrush;
    TToolButton *btnText;
    void __fastcall actAnimatePlayExecute(TObject *Sender);
    void __fastcall actAnimateStopExecute(TObject *Sender);
    void __fastcall actBrushExecute(TObject *Sender);
    void __fastcall actFillExecute(TObject *Sender);
    void __fastcall actFlipHorizontalExecute(TObject *Sender);
    void __fastcall actFlipVerticalExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actModeBlockExecute(TObject *Sender);
    void __fastcall actModePaintExecute(TObject *Sender);
    void __fastcall actMonoOffExecute(TObject *Sender);
    void __fastcall actMonoOnExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall actRotateDownExecute(TObject *Sender);
    void __fastcall actRotateLeft90Execute(TObject *Sender);
    void __fastcall actRotateLeftExecute(TObject *Sender);
    void __fastcall actRotateRight90Execute(TObject *Sender);
    void __fastcall actRotateRightExecute(TObject *Sender);
    void __fastcall actRotateUpExecute(TObject *Sender);
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actSprayBrushExecute(TObject *Sender);
    void __fastcall actTextExecute(TObject *Sender);
    void __fastcall actToggleAnimationExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall FrameEndDock(TObject *Sender, TObject *Target, int X, int Y);
    void __fastcall imgEditorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall panEditorContainerClick(TObject *Sender);
    void __fastcall popAddFrameClick(TObject *Sender);
    void __fastcall popInsertFrameClick(TObject *Sender);
    void __fastcall popRemoveFrameClick(TObject *Sender);
    void __fastcall sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall sbxViewResize(TObject *Sender);
    void __fastcall tmrAnimateTimer(TObject *Sender);

private:    // User declarations
    typedef std::map<int, std::unique_ptr<CanvasTool>> CanvasToolMap;

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

    void            __fastcall  OnDocumentSet();
    void            __fastcall  OnEvent(const Event& event);
    void            __fastcall  DrawGrids();
    void            __fastcall  RefreshView(bool redraw = false);
    void            __fastcall  RefreshFramesView();
    void            __fastcall  OnFrameSelected(TObject *Sender);
    TPoint          __fastcall  ToImagePt(int X, int Y);
    void            __fastcall  SetCanvasColors();
    void            __fastcall  ChangeToolbar(TfrmToolbar* toolbar);

public:        // User declarations
                    __fastcall  TfrmEditorImage(TComponent* Owner);

    __property Project::ImageDocument*  Image = { read = m_ImageDocument, write = m_ImageDocument };
};
//---------------------------------------------------------------------------
#endif
