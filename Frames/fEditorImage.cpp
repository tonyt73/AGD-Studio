//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDDckSite"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::TfrmEditorImage(TComponent* Owner)
: TFrame(Owner)
, m_Magnification(8)
{
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::~TfrmEditorImage()
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSelectExecute(TObject *Sender)
{
    btnTool->ImageIndex = actSelect->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actPencilExecute(TObject *Sender)
{
    btnTool->ImageIndex = actPencil->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actBrushExecute(TObject *Sender)
{
    btnTool->ImageIndex = actBrush->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFillExecute(TObject *Sender)
{
    btnTool->ImageIndex = actFill->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSprayBrushExecute(TObject *Sender)
{
    btnTool->ImageIndex = actSprayBrush->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actEraserExecute(TObject *Sender)
{
    btnTool->ImageIndex = actEraser->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actLineExecute(TObject *Sender)
{
    btnTool->ImageIndex = actLine->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actShapeExecute(TObject *Sender)
{
    btnTool->ImageIndex = actShape->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actTextExecute(TObject *Sender)
{
    btnTool->ImageIndex = actText->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actDropperExecute(TObject *Sender)
{
    btnTool->ImageIndex = actDropper->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actGridPixelExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actGridCharacterExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::FrameEndDock(TObject *Sender, TObject *Target, int X, int Y)
{
    TLMDDockPanel* dp = dynamic_cast<TLMDDockPanel*>(Sender);
    assert(dp != nullptr);
    barStatus->Visible = dp->Site->IsFloatingDoc;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeftExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRightExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateUpExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateDownExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipVerticalExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipHorizontalExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeft90Execute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRight90Execute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOnExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOffExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------

