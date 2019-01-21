//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/BuildManager.h"
#include "Build/BuildMessages.h"
#include "Build/AgdBuilder.h"
#include "Build/AsmBuilder.h"
#include "Build/ChkBuilder.h"
#include "Build/EmuBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall BuildManager::BuildManager()
{
    m_Builders.push_back(std::move(std::make_unique<ChkBuilder>(m_BuildMessages)));
    m_Builders.push_back(std::move(std::make_unique<AgdBuilder>(m_BuildMessages)));
    m_Builders.push_back(std::move(std::make_unique<AsmBuilder>(m_BuildMessages)));
    m_Builders.push_back(std::move(std::make_unique<EmuBuilder>(m_BuildMessages)));
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
    auto start = GetTickCount();
    BUILD_MSG_CLEAR;
    for (auto& builder : m_Builders)
    {
        auto bs = GetTickCount();
        BUILD_MSG_PUSH(builder->Type, builder->Description);
        if (!builder->Execute())
        {
            // failed to execute a build process
            BUILD_LINE(bmFailed, "Build step FAILED");
            auto be = GetTickCount();
            BUILD_LINE(bmFailed, "Elapsed time: " + IntToStr((int)(be - bs)) + "ms");
            BUILD_MSG_POP(false);
            return false;
        }
        BUILD_LINE(bmOk, "Build step completed successfully");
        auto be = GetTickCount();
        BUILD_LINE(bmOk, "Elapsed time: " + IntToStr((int)(be - bs)) + "ms");
        BUILD_MSG_POP(true);
    }
    auto end = GetTickCount();
    BUILD_LINE(bmOk, "Elapsed time: " + IntToStr((int)(end - start)) + "ms");
    return true;
}
//---------------------------------------------------------------------------
