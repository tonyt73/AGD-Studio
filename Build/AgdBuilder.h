//---------------------------------------------------------------------------
#ifndef AgdBuilderH
#define AgdBuilderH
//---------------------------------------------------------------------------
#include <list>
#include "Build/Builder.h"
#include "Build/SectionBuilders/SectionBuilder.h"
//---------------------------------------------------------------------------
class AgdBuilder : public Builder
{
private:
    typedef std::list<std::unique_ptr<SectionBuilders::SectionBuilder>> SectionBuilderList;

    SectionBuilderList           m_SectionBuilders;

public:
                    __fastcall  AgdBuilder(BuildMessages& buildMessages);
    virtual         __fastcall ~AgdBuilder();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
