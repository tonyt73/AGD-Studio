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

    void             SetTreeView(TElXTree* treeView);

public:
                     BuildManager();
    virtual         ~BuildManager();

    bool             Execute();

    __property  TElXTree*       TreeView = { write = SetTreeView };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
