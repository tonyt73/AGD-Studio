//---------------------------------------------------------------------------
#ifndef StringBuilderH
#define StringBuilderH
//---------------------------------------------------------------------------
#include <tuple>
//---------------------------------------------------------------------------
namespace StringBuilders
{
struct Result
{
    Result()
    : Success(false)
    , Reason("Not Implemented") {}

    bool    Success;
    String  Reason;
    String  Content;
};
//---------------------------------------------------------------------------
class StringBuilder
{
private:
    Result                      m_Result;

    void            __fastcall  Clear();

protected:
    void            __fastcall  AddLine(String line);
    void            __fastcall  LineBreak();
    void            __fastcall  Success();
    void            __fastcall  Failure(String reason);

    virtual void    __fastcall  Execute() = 0;

public:
                    __fastcall  StringBuilder();
    virtual         __fastcall ~StringBuilder();

    const Result&   __fastcall  Build();
};
}
//---------------------------------------------------------------------------
#endif
