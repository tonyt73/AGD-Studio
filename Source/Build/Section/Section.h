//---------------------------------------------------------------------------
#ifndef SectionH
#define SectionH
//---------------------------------------------------------------------------
#include <tuple>
#include "..\BuildMessages.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
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
class Section
{
private:
    Result                      m_Result;
    String                      m_Description;

    void            __fastcall  Clear();

protected:
    void            __fastcall  AddLine(String line);
    void            __fastcall  LineBreak();
    void            __fastcall  Success();
    void            __fastcall  Failure(String reason);

    virtual void    __fastcall  Execute() = 0;

public:
                    __fastcall  Section(const String& description);
    virtual         __fastcall ~Section();

    const Result&   __fastcall  Build();

            String  __property  Description = { read = m_Description };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
