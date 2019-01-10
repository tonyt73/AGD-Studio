//---------------------------------------------------------------------------
#ifndef StringBuilderH
#define StringBuilderH
//---------------------------------------------------------------------------
#include <tuple>
//---------------------------------------------------------------------------
namespace StringBuilders
{
//typedef std::tuple<bool, String> Result;
//typedef std::tuple<bool, String, String> BuildResult;

struct Result
{
    Result()
    : Success(false)
    , Reason("Not Implemented") {}

    Result(bool success, String reason, const String& content)
    : Success(success)
    , Reason(reason)
    , Content(content) {}

    bool    Success;
    String  Reason;
    String  Content;
};
//---------------------------------------------------------------------------
class StringBuilder
{
private:
    Result                      m_Result;
protected:

    void            __fastcall  AddLine(String line);
    void            __fastcall  LineBreak();
    void            __fastcall  Success();
    void            __fastcall  Reason(String reason);

    virtual void    __fastcall  Execute() = 0;

public:
                    __fastcall  StringBuilder();
    virtual         __fastcall ~StringBuilder();

    const Result&   __fastcall  Build();
};
}
//---------------------------------------------------------------------------
#endif
