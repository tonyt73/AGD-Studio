//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Creation.h"
#include "AgdSection/ControlsBuilder.h"
#include "AgdSection/EventsBuilder.h"
#include "AgdSection/FontBuilder.h"
#include "AgdSection/JumpTableBuilder.h"
#include "AgdSection/MapBuilder.h"
#include "AgdSection/MessagesBuilder.h"
#include "AgdSection/ObjectsBuilder.h"
#include "AgdSection/ProjectBuilder.h"
#include "AgdSection/SpritesBuilder.h"
#include "AgdSection/TilesBuilder.h"
#include "AgdSection/ScreensBuilder.h"
#include "AgdSection/WindowBuilder.h"
#include "Project/DocumentManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
Creation::Creation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Generate Game File (Project to AGD File)")
{
    m_AgdBuilders.push_back(std::move(std::make_unique<ProjectBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<WindowBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<ControlsBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<MessagesBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<FontBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<JumpTableBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<TilesBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<SpritesBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<ScreensBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<ObjectsBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<MapBuilder>()));
    m_AgdBuilders.push_back(std::move(std::make_unique<EventsBuilder>()));
}
//---------------------------------------------------------------------------
Creation::~Creation()
{
}
//---------------------------------------------------------------------------
bool Creation::Execute()
{
    auto agdFile = Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".agd");
    Project::DocumentManager::get().Add("Text", "AGD", Services::Folders::ProjectName + ".agd");
    String agdContent;
    BUILD_MSG("Building " + agdFile);
    for (auto& builder : m_AgdBuilders)
    {
        auto [success, reason, content] = builder->Build();
        if (success)
        {
            agdContent += content;
            BUILD_LINE(bmOk, "Added AGD Section: " + builder->Description);
        }
        else
        {
            // log an error
            BUILD_LINE(bmFailed, "Failed to add AGD Section: " + builder->Description);
            BUILD_LINE(bmFailed, reason);
            BUILD_MSG(bmFailed);
            return false;
        }
    }

    try
    {
        Services::File::WriteText(agdFile, agdContent);
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

