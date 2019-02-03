//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Creation.h"
#include "Build/SectionBuilders/Project.h"
#include "Build/SectionBuilders/Window.h"
#include "Build/SectionBuilders/Controls.h"
#include "Build/SectionBuilders/JumpTable.h"
#include "Build/SectionBuilders/Messages.h"
#include "Build/SectionBuilders/Events.h"
#include "Build/SectionBuilders/Font.h"
#include "Build/SectionBuilders/Tiles.h"
#include "Build/SectionBuilders/Sprites.h"
#include "Build/SectionBuilders/Objects.h"
#include "Build/SectionBuilders/Map.h"
#include "Build/SectionBuilders/Screens.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Creation::Creation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Generate Game File (Project to AGD File)")
{
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Project>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Window>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Controls>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Messages>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Font>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::JumpTable>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Tiles>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Sprites>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Screens>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Objects>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Map>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Events>()));
}
//---------------------------------------------------------------------------
__fastcall Creation::~Creation()
{
}
//---------------------------------------------------------------------------
bool __fastcall Creation::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    String agdContent;
    BUILD_MSG("Building " + agdFile);
    for (auto& builder : m_SectionBuilders)
    {
        // TODO: change to this when the 64 bit compiler supports C++17
        // auto[success, reason, content] = builder->Build();
        auto result = builder->Build();
        if (result.Success)
        {
            agdContent += result.Content;
            BUILD_LINE(bmOk, "Added AGD Section: " + builder->Description);
        }
        else
        {
            // log an error
            BUILD_LINE(bmFailed, "Failed to add AGD Section: " + builder->Description);
            BUILD_LINE(bmFailed, result.Reason);
            BUILD_MSG(bmFailed);
            return false;
        }
    }

    try
    {
        System::File::WriteText(agdFile, agdContent);
        BUILD_LINE(bmOk, "Successfully wrote AGD file: " + agdFile);
    }
    catch(...)
    {
        BUILD_LINE(bmFailed, "Failed to write AGD file: " + agdFile);
        BUILD_MSG(bmFailed);
        return false;
    }

    BUILD_MSG(bmOk);
    return true;
}
//---------------------------------------------------------------------------

