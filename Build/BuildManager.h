//---------------------------------------------------------------------------
#ifndef BuildManagerH
#define BuildManagerH
//---------------------------------------------------------------------------
#include <list>
#include "Build/BuildMessages.h"
#include "Build/Builder.h"
//---------------------------------------------------------------------------
class BuildManager
{
private:
    typedef     std::list<std::unique_ptr<Builder>> BuildersList;
    BuildersList                m_Builders;
    BuildMessages               m_BuildMessages;

    void            __fastcall  SetTreeView(TElXTree* treeView);

public:
                    __fastcall  BuildManager();
    virtual         __fastcall ~BuildManager();

    bool            __fastcall  Execute();

    __property  TElXTree*       TreeView = { write = SetTreeView };
};
//---------------------------------------------------------------------------
#endif
