//---------------------------------------------------------------------------
#ifndef fToolbarShapeH
#define fToolbarShapeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include "fToolbar.h"
//---------------------------------------------------------------------------
class TfrmToolbarShape : public TfrmToolbar
{
__published:    // IDE-managed Components
    TButton *btnShape;
    TImageList *lstSmall;
    TPopupMenu *popShape;
    TMenuItem *mnuRectangle;
    TMenuItem *mnuEllispse;
    TMenuItem *mnuDiamond;
    TMenuItem *mnuTriangle;
    TMenuItem *mnuRightTriangle;
    TButton *btnFillMode;
    TPopupMenu *popFill;
    TMenuItem *mnuDrawShapeOutline;
    TMenuItem *mnuDrawFilledShape;
    TMenuItem *mnuDrawFilledShapewithOutline;
    TImageList *lstLargeShapes;
    TImageList *imgFills;
    TImageList *imgLargeFill;
    void __fastcall btnFillModeClick(TObject *Sender);
    void __fastcall mnuDrawShapeOutlineClick(TObject *Sender);
    void __fastcall mnuDrawFilledShapewithOutlineClick(TObject *Sender);
    void __fastcall mnuDrawFilledShapeClick(TObject *Sender);
    void __fastcall mnuRectangleClick(TObject *Sender);
    void __fastcall mnuEllispseClick(TObject *Sender);
    void __fastcall mnuDiamondClick(TObject *Sender);
    void __fastcall mnuTriangleClick(TObject *Sender);
    void __fastcall mnuRightTriangleClick(TObject *Sender);
    void __fastcall btnShapeClick(TObject *Sender);
private:    // User declarations
public:     // User declarations
            __fastcall  TfrmToolbarShape(TComponent* Owner);

    Generic __fastcall  Parameters() const;
};
//---------------------------------------------------------------------------
#endif
