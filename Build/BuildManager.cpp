//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "BuildManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall BuildManager::BuildManager()
: m_AgdCompiler(m_BuildMessages)
, m_Assembler(m_BuildMessages)
, m_Emulator(m_BuildMessages)
{

}
//---------------------------------------------------------------------------
__fastcall BuildManager::~BuildManager()
{

}
//---------------------------------------------------------------------------
void __fastcall BuildManager::SetTreeView(TElXTree* treeView)
{
    m_BuildMessages.TreeView = treeView;
}
//---------------------------------------------------------------------------
bool __fastcall BuildManager::Execute()
{
    //BUILD_MSG_CLEAR;
    if (!m_AgdCompiler.Execute())
    {
        // failed to build agd file
        return false;
    }
    if (!m_Assembler.Execute())
    {
        // failed to assemble code
        return false;
    }
    if (!m_Emulator.Execute())
    {
        // failed to run emulator
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
