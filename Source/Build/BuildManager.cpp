//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "BuildManager.h"
#include "BuildMessages.h"
#include "PreChecks.h"
#include "Creation.h"
#include "Compilation.h"
#include "Assemble.h"
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
    if (m_BuildProcesses.size() == 0) {
        m_BuildProcesses.push_back(std::make_unique<PreChecks>(m_BuildMessages));
        m_BuildProcesses.push_back(std::make_unique<Creation>(m_BuildMessages));
        m_BuildProcesses.push_back(std::make_unique<Compilation>(m_BuildMessages));
        m_BuildProcesses.push_back(std::make_unique<Assemble>(m_BuildMessages));
        m_BuildProcesses.push_back(std::make_unique<Emulation>(m_BuildMessages));
    }

    auto buildResult = brOk;
    auto start = GetTickCount();
    BUILD_MSG_CLEAR;
    for (auto& process : m_BuildProcesses) {
        buildResult = brOk;
        auto bs = GetTickCount();
        BUILD_MSG_PUSH(process->Type, process->Description);
        auto buildResult = process->Execute();
        if (buildResult & brError) {
            // failed to execute a build process
            BUILD_LINE(bmFailed, "Build step FAILED");
            buildResult |= brError;
            auto end = GetTickCount();
            BUILD_TIME(end - start);
            return false;
        } else if (buildResult & brWarning) {
            buildResult |= brWarning;
            BUILD_LINE(bmWarning, "Build step completed with warnings");
        } else {
            BUILD_LINE(bmOk, "Build step completed successfully");
        }
        auto be = GetTickCount();
        BUILD_TIME(be - bs);
        BUILD_MSG_POP(buildResult != brOk);
    }
    auto end = GetTickCount();
    BUILD_TIME(end - start);
    return true;
}
//---------------------------------------------------------------------------
