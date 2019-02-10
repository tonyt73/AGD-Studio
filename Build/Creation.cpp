//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Creation.h"
#include "Build/AgdSection/Project.h"
#include "Build/AgdSection/Window.h"
#include "Build/AgdSection/Controls.h"
#include "Build/AgdSection/JumpTable.h"
#include "Build/AgdSection/Messages.h"
#include "Build/AgdSection/Events.h"
#include "Build/AgdSection/Font.h"
#include "Build/AgdSection/Tiles.h"
#include "Build/AgdSection/Sprites.h"
#include "Build/AgdSection/Objects.h"
#include "Build/AgdSection/Map.h"
#include "Build/AgdSection/Screens.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Creation::Creation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Generate Game File (Project to AGD File)")
{
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Project>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Window>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Controls>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Messages>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Font>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::JumpTable>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Tiles>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Sprites>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Screens>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Objects>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Map>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SectionBuilders::Events>()));
}
//---------------------------------------------------------------------------
__fastcall Creation::~Creation()
{
}
//---------------------------------------------------------------------------
bool __fastcall Creation::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    theDocumentManager.Add("Text", "AGD", System::Path::ProjectName + ".agd");
    String agdContent;
    BUILD_MSG("Building " + agdFile);
    for (auto& builder : m_AgdBuilders)
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

