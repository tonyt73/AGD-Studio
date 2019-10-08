//---------------------------------------------------------------------------
#ifndef TreeViewInterceptorH
#define TreeViewInterceptorH
//---------------------------------------------------------------------------
#include "Interceptor.h"
//---------------------------------------------------------------------------
class TTreeViewInterceptor : public Interceptor
{
private:
    void    __fastcall  OnAfter(const String& MethodName, const TArgs Args, TValue &Result);

public:
            __fastcall  TTreeViewInterceptor(TObject* object);
};
//---------------------------------------------------------------------------
#endif

