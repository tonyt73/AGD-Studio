//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fToolbarShape.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fToolbar"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmToolbarShape::TfrmToolbarShape(TComponent* Owner)
: TfrmToolbar(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::btnFillModeClick(TObject *Sender)
{
    switch (btnFillMode->ImageIndex)
    {
        case 0: mnuDrawFilledShapeClick(nullptr); break;
        case 1: mnuDrawFilledShapewithOutlineClick(nullptr); break;
        case 2: mnuDrawShapeOutlineClick(nullptr); break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuDrawShapeOutlineClick(TObject *Sender)
{
    btnFillMode->ImageIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuDrawFilledShapeClick(TObject *Sender)
{
    btnFillMode->ImageIndex = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuDrawFilledShapewithOutlineClick(TObject *Sender)
{
    btnFillMode->ImageIndex = 2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::btnShapeClick(TObject *Sender)
{
    switch (btnShape->ImageIndex)
    {
        case 0: mnuEllispseClick(nullptr); break;
        case 1: mnuDiamondClick(nullptr); break;
        case 2: mnuTriangleClick(nullptr); break;
        case 3: mnuRightTriangleClick(nullptr); break;
        case 4: mnuRectangleClick(nullptr); break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuRectangleClick(TObject *Sender)
{
    btnShape->ImageIndex = 0;
    btnShape->Caption = "Rectangle";
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuEllispseClick(TObject *Sender)
{
    btnShape->ImageIndex = 1;
    btnShape->Caption = "Ellipse";
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuDiamondClick(TObject *Sender)
{
    btnShape->ImageIndex = 2;
    btnShape->Caption = "Diamond";
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuTriangleClick(TObject *Sender)
{
    btnShape->ImageIndex = 3;
    btnShape->Caption = "Triangle";
}
//---------------------------------------------------------------------------
void __fastcall TfrmToolbarShape::mnuRightTriangleClick(TObject *Sender)
{
    btnShape->ImageIndex = 4;
    btnShape->Caption = "Right Triangle";
}
//---------------------------------------------------------------------------
Services::Generic __fastcall TfrmToolbarShape::Parameters() const
{
    Services::Generic parameters;
    parameters.Add("Shape", btnShape->ImageIndex);
    parameters.Add("Fill", btnFillMode->ImageIndex);
    return parameters;
}
//---------------------------------------------------------------------------
