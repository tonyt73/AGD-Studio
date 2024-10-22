//---------------------------------------------------------------------------
#ifndef CreationH
#define CreationH
//---------------------------------------------------------------------------
#include <list>
#include "BuildProcess.h"
#include "AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Creation : public BuildProcess
{
private:
    typedef std::list<std::unique_ptr<SectionBuilder>> SectionBuilderList;

    SectionBuilderList           m_AgdBuilders;

public:
                    __fastcall  Creation(BuildMessages& buildMessages);
    virtual         __fastcall ~Creation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
