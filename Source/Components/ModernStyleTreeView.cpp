//---------------------------------------------------------------------------
#include <Vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Themes.hpp>
#include "ModernStyleTreeView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TModernStyleTreeView *)
{
  new TModernStyleTreeView(NULL);
}
//---------------------------------------------------------------------------
__fastcall TModernStyleTreeView::TModernStyleTreeView(TComponent* Owner)
: TTreeView(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TModernStyleTreeView::CreateWnd()
{
    TTreeView::CreateWnd();
    SetWindowTheme(Handle, L"Explorer", NULL);
}
//---------------------------------------------------------------------------
namespace Modernstyletreeview
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TModernStyleTreeView)};
        RegisterComponents("Scorpio", classes, 0);
    }
}//---------------------------------------------------------------------------

