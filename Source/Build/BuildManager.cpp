//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "BuildManager.h"
#include "BuildMessages.h"
#include "PreChecks.h"
#include "Creation.h"
#include "Compilation.h"
#include "Assembly.h"
#include "Emulation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall BuildManager::BuildManager()
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
    if (m_BuildProcesses.size() == 0)
    {
        m_BuildProcesses.push_back(std::move(std::make_unique<PreChecks>(m_BuildMessages)));
        m_BuildProcesses.push_back(std::move(std::make_unique<Creation>(m_BuildMessages)));
        m_BuildProcesses.push_back(std::move(std::make_unique<Compilation>(m_BuildMessages)));
        m_BuildProcesses.push_back(std::move(std::make_unique<Assembly>(m_BuildMessages)));
        m_BuildProcesses.push_back(std::move(std::make_unique<Emulation>(m_BuildMessages)));
    }

    auto start = GetTickCount();
    BUILD_MSG_CLEAR;
    for (auto& process : m_BuildProcesses)
    {
        auto bs = GetTickCount();
        BUILD_MSG_PUSH(process->Type, process->Description);
        if (!process->Execute())
        {
            // failed to execute a build process
            BUILD_LINE(bmFailed, "Build step FAILED");
            auto be = GetTickCount();
            BUILD_TIME(be - bs);
            BUILD_MSG_POP(false);
            return false;
        }
        BUILD_LINE(bmOk, "Build step completed successfully");
        auto be = GetTickCount();
        BUILD_TIME(be - bs);
        BUILD_MSG_POP(true);
    }
    auto end = GetTickCount();
    BUILD_TIME(end - start);
    return true;
}
//---------------------------------------------------------------------------
