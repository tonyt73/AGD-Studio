//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include "Interceptor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Interceptor::Interceptor(TObject* object)
: m_Object(object)
{
    m_vmi = std::make_unique<TVirtualMethodInterceptor>(m_Object->ClassType());
    m_vmi->OnAfter = [=](System::TObject* Instance, TRttiMethod* Method, const TArgs Args, TValue &Result)
    {
        DoAfter(Instance, Method, Args, Result);
    };
    m_vmi->OnBefore = [=](System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &DoInvoke, TValue &Result)
    {
        DoBefore(Instance, Method, Args, DoInvoke, Result);
    };
    m_vmi->OnException = [=](System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &RaiseException, System::Sysutils::Exception* TheException, TValue &Result)
    {
        this->DoException(Instance, Method, Args, RaiseException, TheException, Result);
    };
    m_vmi->Proxify(m_Object);
}
//---------------------------------------------------------------------------
__fastcall Interceptor::~Interceptor()
{
    m_vmi->Unproxify(m_Object);
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::InterceptOnAfter(const String& MethodName)
{
    TRttiContext ctx;
    auto method = ctx.GetType(m_Object->ClassType())->GetMethod(MethodName);
    if (method)
    {
        m_AfterMethods[MethodName] = method;
    }
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::InterceptOnBefore(const String& MethodName)
{
    TRttiContext ctx;
    auto method = ctx.GetType(m_Object->ClassType())->GetMethod(MethodName);
    if (method)
    {
        m_BeforeMethods[MethodName] = method;
    }
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::DoBefore(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &DoInvoke, TValue &Result)
{
    assert(m_Object == Instance);
    if (m_BeforeMethods[Method->Name])
    {
        OnBefore(Method->Name, Args, DoInvoke, Result);
    }
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::DoAfter(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, TValue &Result)
{
    assert(m_Object == Instance);
    if (m_AfterMethods[Method->Name])
    {
        OnAfter(Method->Name, Args, Result);
    }
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::DoException(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &RaiseException, System::Sysutils::Exception* TheException, TValue &Result)
{
    assert(m_Object == Instance);
    if (m_AfterMethods[Method->Name])
    {
        OnException(Method->Name, Args, RaiseException, TheException, Result);
    }
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::OnBefore(const String& MethodName, const TArgs Args, bool &DoInvoke, TValue &Result)
{
    // do nothing
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::OnAfter(const String& MethodName, const TArgs Args, TValue &Result)
{
    // do nothing
}
//---------------------------------------------------------------------------
void __fastcall Interceptor::OnException(const String& MethodName, const TArgs Args, bool &RaiseException, System::Sysutils::Exception* TheException, TValue &Result)
{
    // do nothing
}
//---------------------------------------------------------------------------

