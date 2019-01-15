//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "AgdBuilder.h"
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
__fastcall AgdBuilder::AgdBuilder(BuildMessages& buildMessages)
: Builder(buildMessages)
{
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Project>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Window>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Controls>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::JumpTable>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Messages>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Font>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Tiles>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Sprites>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Screens>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Objects>()));
    m_SectionBuilders.push_back(std::move(std::make_unique<SectionBuilders::Events>()));
}
//---------------------------------------------------------------------------
__fastcall AgdBuilder::~AgdBuilder()
{
}
//---------------------------------------------------------------------------
bool __fastcall AgdBuilder::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    String agdContent;
    for (auto& builder : m_SectionBuilders)
    {
        // TODO: change to this when the 64 bit compiler supports C++17
        // auto[success, reason, content] = builder->Build();
        auto result = builder->Build();
        if (result.Success)
        {
            agdContent += result.Content;
        }
        else
        {
            // log an error
            return false;
        }
    }

    System::File::WriteText(agdFile, agdContent);

    return true;
}
//---------------------------------------------------------------------------

