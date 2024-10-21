//---------------------------------------------------------------------------
#ifndef BuildManagerH
#define BuildManagerH
//---------------------------------------------------------------------------
#include <list>
#include "Build/BuildMessages.h"
#include "Build/BuildProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class BuildManager
{
private:
    typedef std::list<std::unique_ptr<BuildProcess>> BuildProcesses;
    BuildProcesses              m_BuildProcesses;
    BuildMessages               m_BuildMessages;

    void            __fastcall  SetTreeView(TElXTree* treeView);

public:
                    __fastcall  BuildManager();
    virtual         __fastcall ~BuildManager();

    bool            __fastcall  Execute();

    __property  TElXTree*       TreeView = { write = SetTreeView };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
