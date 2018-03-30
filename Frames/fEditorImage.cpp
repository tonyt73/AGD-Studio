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
{
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::~TfrmEditorImage()
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSelectRectangleExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actSelectRectangle->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actZoom->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actPencilExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actPencil->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actBrushExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actBrush->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actPaintBucketExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actPaintBucket->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSprayBrushExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actSprayBrush->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actStampExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actStamp->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actEraserExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actEraser->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actDrawLineExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actDrawLine->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actDrawShapeExecute(TObject *Sender)
{
	//btnTool->ImageIndex = actDrawShape->ImageIndex;
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
void __fastcall TfrmEditorImage::actTextExecute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actDropperExecute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action3Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action4Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action5Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action6Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action7Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action8Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action9Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action10Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action11Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action12Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action13Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action14Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action15Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::Action16Execute(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::FrameEndDock(TObject *Sender, TObject *Target, int X, int Y)
{
    TLMDDockPanel* dp = dynamic_cast<TLMDDockPanel*>(Sender);
    assert(dp != nullptr);
    StatusBar1->Visible = dp->Site->IsFloatingDoc;
}
//---------------------------------------------------------------------------

