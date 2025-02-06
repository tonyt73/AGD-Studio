//---------------------------------------------------------------------------
#ifndef CreationH
#define CreationH
//---------------------------------------------------------------------------
#include <list>
#include "BuildProcess.h"
#include "Section/Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Creation final : public BuildProcess
{
private:
    typedef std::list<std::unique_ptr<Section>> SectionList;

    SectionList         m_AgdSections;

public:
            __fastcall  Creation(BuildMessages& buildMessages);
            __fastcall ~Creation() final;

    int     __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
