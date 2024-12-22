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
class Creation : public BuildProcess
{
private:
    typedef std::list<std::unique_ptr<Section>> SectionList;

    SectionList         m_AgdSections;

public:
            __fastcall  Creation(BuildMessages& buildMessages);
    virtual __fastcall ~Creation() override;

    bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
