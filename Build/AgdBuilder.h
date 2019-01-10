//---------------------------------------------------------------------------
#ifndef AgdBuilderH
#define AgdBuilderH
//---------------------------------------------------------------------------
#include <list>
#include "Build/Builder.h"
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
class AgdBuilder : public Builder
{
private:
    typedef std::list<std::unique_ptr<StringBuilders::StringBuilder>> StringBuilderList;

    StringBuilderList           m_StringBuilders;

public:
                    __fastcall  AgdBuilder(BuildMessages& buildMessages);
    virtual         __fastcall ~AgdBuilder();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
