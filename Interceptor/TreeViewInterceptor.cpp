//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TreeViewInterceptor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TTreeViewInterceptor::TTreeViewInterceptor(TObject* object)
: Interceptor(object)
{
    InterceptOnAfter("CreateWnd");
}
//---------------------------------------------------------------------------
void __fastcall TTreeViewInterceptor::OnAfter(const String& MethodName, const TArgs Args, TValue &Result)
{
    SetWindowTheme(((TWinControl*)Object)->Handle, L"Explorer", NULL);
}
//---------------------------------------------------------------------------

