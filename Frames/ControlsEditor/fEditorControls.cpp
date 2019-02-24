//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorControls.h"
#include "Project/DocumentManager.h"
#include "Project/EditorManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorControls::TfrmEditorControls(TComponent* Owner)
: TFrame(Owner)
{
//    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
//    const auto& gm = *(mc.GraphicsMode());
//    m_View = make_unique<TBitmap>();
//    m_View->PixelFormat = pf32bit;
//    m_View->Width = gm.Width / mc.ImageSizing[itCharacterSet].Minimum.Width;
//    m_View->Height = gm.Height / mc.ImageSizing[itCharacterSet].Minimum.Height;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::SetDocument(Document* document)
{
    m_Document = dynamic_cast<ControlsDocument*>(document);
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorControls::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::ShowKeysHelp()
{
    const String help = "TODO: ???\r\n";
    ::Messaging::Bus::Publish<MessageEvent>(HelpKeysMessageEvent(help));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

