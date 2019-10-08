//---------------------------------------------------------------------------
#ifndef InterceptorH
#define InterceptorH
//---------------------------------------------------------------------------
#include <System.Rtti.hpp>
#include <map>
//---------------------------------------------------------------------------
class Interceptor
{
private:
    typedef std::unique_ptr<TVirtualMethodInterceptor> TVmiPtr;
    TVmiPtr                         m_vmi;
    std::map<String, TRttiMethod*>  m_AfterMethods;
    std::map<String, TRttiMethod*>  m_BeforeMethods;
    TObject*                        m_Object;

protected:

#ifndef _WIN64
    typedef const TArgs TArgs;
#else /* _WIN64 */
    typedef System::TArray__1<TValue> TArgs;
#endif /* _WIN64 */

    // default handlers
            void    __fastcall  DoBefore(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &DoInvoke, TValue &Result);
            void    __fastcall  DoAfter(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, TValue &Result);
            void    __fastcall  DoException(System::TObject* Instance, TRttiMethod* Method, const TArgs Args, bool &RaiseException, System::Sysutils::Exception* TheException, TValue &Result);

    // inherited classes overrides/handlers
    virtual void    __fastcall  OnBefore(const String& MethodName, const TArgs Args, bool &DoInvoke, TValue &Result);
    virtual void    __fastcall  OnAfter(const String& MethodName, const TArgs Args, TValue &Result);
    virtual void    __fastcall  OnException(const String& MethodName, const TArgs Args, bool &RaiseException, System::Sysutils::Exception* TheException, TValue &Result);

            void    __fastcall  InterceptOnAfter(const String& MethodName);
            void    __fastcall  InterceptOnBefore(const String& MethodName);
            void    __fastcall  InterceptOnException(const String& MethodName);

    __property  TObject*        Object = { read = m_Object };

public:
                    __fastcall  Interceptor(TObject* object);
                    __fastcall ~Interceptor();
};
//---------------------------------------------------------------------------
#endif

