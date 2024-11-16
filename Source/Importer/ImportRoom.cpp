//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ImportRoom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImportRoom::ImportRoom(const String& data, unsigned int screenIndex)
{
    try
    {
        // convert the SPRITEPOSITION commands
        auto ld = data.LowerCase();
        auto sp = ld.Pos("spriteposition");
        auto sprites = sp != 0 ? data.SubString(sp, data.Length()) : "";
        auto blocks = sp != 0 ? data.SubString(1, sp - 1) : data;
        auto spTokens = SplitString(sprites.Trim(), " ");
        String  prevToken = "";
        SpritePosition spritePos;
        spritePos.ScreenIndex = screenIndex;
        int i = 0;
        for (auto token : spTokens)
        {
            token = token.Trim();
            if (token != "")
            {
                if (prevToken.LowerCase() == "spriteposition")
                {
                    i = 1;
                    spritePos.Type = StrToInt(token);
                }
                else if (i == 1)
                {
                    spritePos.Index = StrToInt(token);
                    if (spritePos.Index == 90)
                    {
                        spritePos.Index = 0;
                    }
                    i = 2;
                }
                else if (i == 2)
                {
                    spritePos.Position.Y = StrToInt(token);
                    i = 3;
                }
                else if (i == 3)
                {
                    spritePos.Position.X = StrToInt(token);
                    i = 0;
                    m_Sprites.push_back(spritePos);
                }
                prevToken = token;
            }
        }

        // Convert the block data
        auto tokens = SplitString(blocks.Trim(), " ");
        for (auto token : tokens)
        {
            if (token.Trim() != "")
            {
                m_Blocks.push_back(StrToInt(token.Trim()));
            }
        }
    }
    catch(...)
    {
        //g_ErrorReporter.Add("Error: Exception caught while converting Scrren data. [" + data + "]");
        throw;
    }
}
//---------------------------------------------------------------------------
