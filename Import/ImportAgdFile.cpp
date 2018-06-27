//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.StrUtils.hpp>
#include "ImportAgdFile.h"
#include "Messaging.h"
#include "Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImportAgdFile::ImportAgdFile()
{
}
//---------------------------------------------------------------------------
bool __fastcall ImportAgdFile::Process(const String& file)
{
    if (TFile::Exists(file))
    {
        Information("File found. [" + file + "]");
        // Load the file
        auto lines = System::Ioutils::TFile::ReadAllLines(file);
        try
        {
            Information("Processing file: [" + file + "]");
            String data = "";
            for (auto line : lines)
            {
                // find image marker
                auto tline = String(line).Trim().LowerCase();
                // remove comments
                auto cPos = tline.Pos("ª");
                if (cPos > 0)
                {
                    tline = tline.SubString(1, cPos - 1);
                }
                if (tline.Length() > 0)
                {
                    // process the line
                    if (tline.Pos("define") > 0 || tline.Pos("map") > 0)
                    {
                        if (tline.Pos("endmap") == 1)
                        {
                            ConvertMap(data);
                            data = "";
                        }
                        else if (data.Length() > 0)
                        {
                            // convert data
                            Convert(data);
                        }
                        // defining something
                        data = tline;
                    }
                    else
                    {
                        data += " " + tline;
                    }
                }
            }
            return true;
        }
        catch(...)
        {
            Error("Exception caught while processing file. [" + file + "]");
        }
    }
    else
    {
        Error("File not found. [" + file + "]");
    }
    return false;
}
//---------------------------------------------------------------------------
String __fastcall ImportAgdFile::PreProcess(const String& data) const
{
    String line;
    auto sPos = data.Pos(' ');
    auto tPos = data.Pos('\t');
    Information("Preprocessing...");
    try
    {
        sPos = sPos != 0 && tPos != 0 ? std::min(sPos, tPos) : (sPos == 0 ? tPos : sPos);
        // remove the define/map/endmap statement
        line = data.SubString(sPos, data.Length()).Trim();
        // replace all newlines + tabs with space
        int rPos, nPos;
        do
        {
            rPos = line.Pos("\r");
            if (rPos > 0)
            {
                line = line.SubString(1, rPos - 1) + + " " + line.SubString(rPos + 1, line.Length());
            }
            nPos = line.Pos("\n");
            if (nPos > 0)
            {
                line = line.SubString(1, nPos - 1) + + " " + line.SubString(nPos + 1, line.Length());
            }
            tPos = line.Pos("\t");
            if (tPos > 0)
            {
                line = line.SubString(1, tPos - 1) + " " + line.SubString(tPos + 1, line.Length());
            }

        }
        while (rPos != 0 || nPos != 0 || tPos != 0);
    }
    catch(...)
    {
        Error("Exception caught while pre-processing white space");
        throw;
    }
    // change ',' to ' '
    for (auto i = 1; i <= line.Length(); i++)
    {
         if (line[i] == ',')
         {
            line[i] = ' ';
         }
    }
    // all data should now be on 1 line

    // convert hex to decimal
    try
    {
        int hPos = 0;
        do
        {
            hPos = line.Pos("$");
            if (hPos > 0)
            {
                auto l1 = line.SubString(1, hPos - 1).Trim();
                auto l2 = line.SubString(hPos + 1, line.Length());
                auto l3 = String();
                sPos = l2.Pos(' ');
                if (sPos > 0)
                {
                    l3 = l2.SubString(sPos, l2.Length()).Trim();
                    l2 = l2.SubString(1, sPos).Trim();
                }
                auto value = StrToInt("0x" + l2);
                line = l1 + " " + IntToStr(value) + " " + l3;
            }
        }
        while (hPos != 0);
    }
    catch(...)
    {
        Error("Exception caught while pre-processing hex into decimal");
        throw;
    }
    return line.Trim();
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::Convert(const String& data)
{
    try
    {
        if (data.Pos("definemessages") == 0)
        {
            auto pdata = PreProcess(data);
            if (data.Pos("defineblock") == 1)
            {
                ConvertBlock(pdata);
            }
            else if (data.Pos("defineobject") == 1)
            {
                ConvertObject(pdata);
            }
            else if (data.Pos("definesprite") == 1)
            {
                ConvertSprite(pdata);
            }
            else if (data.Pos("definefont") == 1)
            {
                ConvertFont(pdata);
            }
            else if (data.Pos("definewindow") == 1)
            {
                ConvertWindow(pdata);
            }
            else if (data.Pos("definescreen") == 1)
            {
                ConvertScreen(pdata);
            }
        }
        else
        {
            ConvertMessages(data);
        }
    }
    catch(...)
    {
        Error("Exception caught while converting data to valid AGD type");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertScreen(const String& data)
{
    try
    {
        // convert the data
        //m_Screens.push_back(std::move(std::make_unique<GameScreen>(data)));
    }
    catch(...)
    {
        Error("Exception caught while converting Screen data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertMap(const String& data)
{
    try
    {
        auto pdata = PreProcess(data);
        //m_Map = std::make_unique<Map>(pdata);
    }
    catch(...)
    {
        Error("Exception caught while converting Map data");
        Error("Exception caught while converting Map data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertWindow(const String& data)
{
    TPoint position;
    TSize  size;
    try
    {
        auto tokens = SplitString(data, " ");
        auto i = 0;
        for (auto token : tokens)
        {
            switch(i++)
            {
                case 0: position.Y = StrToInt(token); break;
                case 1: position.X = StrToInt(token); break;
                case 2: size.cx = StrToInt(token); break;
                case 3: size.cy = StrToInt(token); break;
            }
        }
    }
    catch(...)
    {
        Error("Exception caught while converting Window data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertBlock(const String& data)
{
    try
    {
        // convert the data
        // get the type
        auto tPos = data.Pos(" ");
        auto subType = data.SubString(1, tPos - 1);
        auto idata = data.SubString(tPos + 1, data.Length());
        //m_Blocks.push_back(std::move(std::make_unique<ImageBlock>(subType, idata)));
    }
    catch(...)
    {
        Error("Exception caught while converting Block data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertObject(const String& data)
{
    try
    {
        // convert the data
        //m_Objects.push_back(std::move(std::make_unique<ImageObject>(data)));
    }
    catch(...)
    {
        Error("Exception caught while converting Object data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertSprite(const String& data)
{
    try
    {
        // convert the data
        //m_Sprites.push_back(std::move(std::make_unique<ImageSprite>(data)));
    }
    catch(...)
    {
        Error("Exception caught while converting Sprite data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertFont(const String& data)
{
    try
    {
        // convert the data
        //m_Font.push_back(std::move(std::make_unique<ImageFont>(data)));
    }
    catch(...)
    {
        Error("Exception caught while converting Font data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImportAgdFile::ConvertMessages(const String& data)
{
    try
    {
        // convert the data
        auto mPos = data.Pos(" ");
        auto mdata = data.SubString(mPos + 1, data.Length());
        auto tokens = SplitString(mdata, "\"");
        for (auto token : tokens)
        {
            token = token.Trim();
            if (token != "")
            {
                ::Messaging::Bus::Publish<OnImportMessage>(OnImportMessage(token));
            }
        }
    }
    catch(...)
    {
        Error("Exception caught while converting Message data");
        throw;
    }
}
//---------------------------------------------------------------------------
