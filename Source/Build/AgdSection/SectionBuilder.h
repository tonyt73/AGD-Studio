//---------------------------------------------------------------------------
#ifndef SectionBuilderH
#define SectionBuilderH
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
class SectionBuilder
{
private:
    Result                      m_Result;
    String                      m_Description;

    void             Clear();

protected:
    void             AddLine(String line);
    void             LineBreak();
    void             Success();
    void             Failure(String reason);

    virtual void     Execute() = 0;

public:
                     SectionBuilder(const String& description);
    virtual         ~SectionBuilder();

    const Result&    Build();

            String  __property  Description = { read = m_Description };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
