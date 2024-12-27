//---------------------------------------------------------------------------
#ifndef fToolbarShapeH
#define fToolbarShapeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include "fToolbar.h"
//---------------------------------------------------------------------------
class TfrmToolbarShape : public TfrmToolbar
{
__published:    // IDE-managed Components
    TButton *btnFillMode;
    TButton *btnShape;
    TImageList *imgFills;
    TImageList *imgLargeFill;
    TImageList *lstLargeShapes;
    TImageList *lstSmall;
    TMenuItem *mnuDiamond;
    TMenuItem *mnuDrawFilledShape;
    TMenuItem *mnuDrawFilledShapewithOutline;
    TMenuItem *mnuDrawShapeOutline;
    TMenuItem *mnuEllispse;
    TMenuItem *mnuRectangle;
    TMenuItem *mnuRightTriangle;
    TMenuItem *mnuTriangle;
    TPopupMenu *popFill;
    TPopupMenu *popShape;
    void __fastcall btnFillModeClick(TObject *Sender);
    void __fastcall btnShapeClick(TObject *Sender);
    void __fastcall mnuDiamondClick(TObject *Sender);
    void __fastcall mnuDrawFilledShapeClick(TObject *Sender);
    void __fastcall mnuDrawFilledShapewithOutlineClick(TObject *Sender);
    void __fastcall mnuDrawShapeOutlineClick(TObject *Sender);
    void __fastcall mnuEllispseClick(TObject *Sender);
    void __fastcall mnuRectangleClick(TObject *Sender);
    void __fastcall mnuRightTriangleClick(TObject *Sender);
    void __fastcall mnuTriangleClick(TObject *Sender);

private:    // User declarations
public:     // User declarations
                      __fastcall  TfrmToolbarShape(TComponent* Owner) override;

    Services::Generic __fastcall  Parameters() const;
};
//---------------------------------------------------------------------------
#endif
