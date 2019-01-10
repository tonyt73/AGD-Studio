//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "AgdBuilder.h"
#include "Build/StringBuilders/Project.h"
#include "Build/StringBuilders/Window.h"
#include "Build/StringBuilders/Controls.h"
#include "Build/StringBuilders/JumpTable.h"
#include "Build/StringBuilders/Messages.h"
#include "Build/StringBuilders/Events.h"
#include "Build/StringBuilders/Font.h"
#include "Build/StringBuilders/Tiles.h"
#include "Build/StringBuilders/Sprites.h"
#include "Build/StringBuilders/Objects.h"
#include "Build/StringBuilders/Map.h"
#include "Build/StringBuilders/Screens.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall AgdBuilder::AgdBuilder(BuildMessages& buildMessages)
: Builder(buildMessages)
{
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Project>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Window>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Controls>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::JumpTable>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Messages>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Events>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Font>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Tiles>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Sprites>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Objects>()));
    m_StringBuilders.push_back(std::move(std::make_unique<StringBuilders::Screens>()));
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

    for (auto& builder : m_StringBuilders)
    {
        // TODO: change to this when the 64 bit compiler supports it
        //auto[success, reason, content] = builder->Build();
        auto result = builder->Build();
        if (result.Success)
        {
            agdContent += result.Content;
        }
        else
        {
            // log an error
            //return false;
        }
    }

    System::File::WriteText(agdFile, agdContent);

    return true;
}
//---------------------------------------------------------------------------


//
//    String content = ";DEFINEMACHINE \"" + System::Path::Machine + "\"\r\n";
//
//    content += "\r\nDEFINEWINDOW " + IntToStr(m_WindowEditor.y) + " " + IntToStr(m_WindowEditor.x) + " " + IntToStr(m_WindowEditor.h) + " " + IntToStr(m_WindowEditor.w) + "\r\n";
//
//    content += "\r\nDEFINECONTROLS  'Q' 'A' 'O' 'P' ' ' 'Z' 'I'\r\n";
//
//    content += "\r\n" + m_JumpEditor.Get() + "\r\n";
//
//    content += "\r\nDEFINEMESSAGES\r\n";
//    for (const auto &msg : m_Messages)
//    {
//        auto m = ReplaceText(msg, "\n", "");
//        content += "    \"" + m + "\r\"\r\n";
//    }
//
//    // font
//    content += "\r\nDEFINEFONT ";
//    if (m_Font.size() == 1)
//    {
//        BitmapData data;
//        for (const auto &chr : m_Font)
//        {
//            String line;
//            chr->GetBitmapData(data);
//            int i = 0;
//            for (auto byte : data)
//            {
//                line += IntToStr(byte) + " ";
//                if ((++i % 8) == 0)
//                {
//                    content += line + "\r\n           ";
//                    line = "";
//                }
//            }
//        }
//    }
//
//    // jump table
//    content += "\r\n" + m_JumpEditor.Get() + "\r\n";
//
//    // blocks
//    if (m_Blocks.size() != 0)
//    {
//        for (const auto &blk : m_Blocks)
//        {
//            content += "\r\nDEFINEBLOCK " + blk->SubType + "            \r\n            ";
//            BitmapData data;
//            blk->GetBitmapData(data);
//            for (auto b : data)
//            {
//                content += IntToStr(b) + " ";
//            }
//            content += "\r\n            " + IntToStr(blk->Attribute) + "\r\n";
//        }
//    }
//
//    // sprites
//    if (m_Sprites.size() != 0)
//    {
//        for (const auto &spr : m_Sprites)
//        {
//            content += "\r\nDEFINESPRITE " + IntToStr(spr->Frames) + "\r\n             ";
//            BitmapData data;
//            spr->GetBitmapData(data);
//            auto stride = spr->Height * 2;
//            for (auto f = 0; f< spr->Frames; f++)
//            {
//                for (auto i = 0; i< stride; i++)
//                {
//                    content += IntToStr(data[f * stride + i]) + " ";
//                }
//                content += "\r\n             ";
//            }
//        }
//    }
//
//    // screen
//    if (m_Screens.size() != 0)
//    {
//        for (const auto &room : m_Screens)
//        {
//            content += "\r\nDEFINESCREEN ";
//            int w = 0;
//            for (auto blk : room->m_Blocks)
//            {
//                content += IntToStr(blk) + " ";
//                if (++w % m_WindowEditor.w == 0)
//                {
//                    content += "\r\n             ";
//                }
//            }
//            for (const auto &s : room->m_Sprites)
//            {
//                content += "\r\nSPRITEPOSITION " + IntToStr(s.Type) + " " + IntToStr(s.Index) + " " + IntToStr((int)s.Position.Y) + " " + IntToStr((int)s.Position.X);
//            }
//            content += "\r\n";
//        }
//    }
//
//    // object
//    if (m_Objects.size() != 0)
//    {
//        for (const auto &obj : m_Objects)
//        {
//            const auto& o = dynamic_cast<ImageObject *> (obj.get());
//            content += "\r\nDEFINEOBJECT " + IntToStr(o->Attribute) + " " + IntToStr(o->Room) + " " + IntToStr((int)o->Position.Y) + " " + IntToStr((int)o->Position.X) + "\r\n             ";
//            BitmapData data;
//            obj->GetBitmapData(data);
//            for (auto b : data)
//            {
//                content += IntToStr(b) + " ";
//            }
//            content += "\r\n";
//        }
//    }
//
//    if (m_Map != nullptr)
//    {
//        // map
//        content += "\r\nMAP WIDTH " + IntToStr(m_Map->Width) + "\r\n    STARTSCREEN " + IntToStr(m_Map->StartScreen) + "\r\n    ";
//        auto i = 0;
//        for (auto d : m_Map->MapData)
//        {
//            content += IntToStr(d) + " ";
//            if (++i % m_Map->Width == 0)
//            {
//                content += "\r\n    ";
//            }
//        }
//        content += "\r\nENDMAP\r\n\r\n";
//    }
//    // events
//    String ll = "";
//    for (auto l : memAGD->Lines)
//    {
//        if (l.Trim() != "")
//        {
//            if (ll == "")
//            {
//                content += "\n";
//            }
//            content += l + "\n";
//        }
//        ll = l.Trim();
//    }

