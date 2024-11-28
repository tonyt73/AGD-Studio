//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Creation.h"
#include "Project/Documents/DocumentManager.h"
#include "Section/ControlsSection.h"
#include "Section/EventsSection.h"
#include "Section/FontSection.h"
#include "Section/JumpTableSection.h"
#include "Section/MapSection.h"
#include "Section/MessagesSection.h"
#include "Section/ObjectsSection.h"
#include "Section/ProjectSection.h"
#include "Section/SpritesSection.h"
#include "Section/TilesSection.h"
#include "Section/ScreensSection.h"
#include "Section/WindowSection.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Creation::Creation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Generate Game File (Project to AGD File)")
{
    m_AgdSections.push_back(std::move(std::make_unique<ProjectSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<WindowSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<ControlsSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<MessagesSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<FontSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<JumpTableSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<TilesSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<ObjectsSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<SpritesSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<ScreensSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<MapSection>()));
    m_AgdSections.push_back(std::move(std::make_unique<EventsSection>()));
}
//---------------------------------------------------------------------------
__fastcall Creation::~Creation()
{
}
//---------------------------------------------------------------------------
bool __fastcall Creation::Execute()
{
    auto agdFile = Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".agd");
    Project::DocumentManager::get().Add("Text", "AGD", Services::Folders::ProjectName + ".agd");
    String agdContent;
    BUILD_MSG("Building " + agdFile);
    for (auto& builder : m_AgdSections)
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

