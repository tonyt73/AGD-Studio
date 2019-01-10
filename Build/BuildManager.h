//---------------------------------------------------------------------------
#ifndef BuildManagerH
#define BuildManagerH
//---------------------------------------------------------------------------
#include "Build/BuildMessages.h"
#include "Build/AgdBuilder.h"
#include "Build/AsmBuilder.h"
#include "Build/EmuBuilder.h"
//---------------------------------------------------------------------------
class BuildManager
{
private:
    BuildMessages               m_BuildMessages;
    AgdBuilder                  m_AgdCompiler;
    AsmBuilder                  m_Assembler;
    EmuBuilder                  m_Emulator;

    void            __fastcall  SetTreeView(TElXTree* treeView);

public:
                    __fastcall  BuildManager();
    virtual         __fastcall ~BuildManager();

    bool            __fastcall  Execute();

    __property  TElXTree*       TreeView = { write = SetTreeView };
};
//---------------------------------------------------------------------------
#endif
