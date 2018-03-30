//---------------------------------------------------------------------------
#include "Arcadium.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "CharacterSet.h"
#include "FileSystem/Path.h"
#include "FileSystem/File.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace std;
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
__fastcall CharacterSet::CharacterSet(const String& file)
: m_Bitmap(nullptr)
, m_File(file)
{
}
//---------------------------------------------------------------------------
__fastcall CharacterSet::~CharacterSet()
{
}
//---------------------------------------------------------------------------
String __fastcall CharacterSet::GetName()
{
    return FileSystem::File::NameWithoutExtension(m_File);
}
//---------------------------------------------------------------------------
TBitmap* __fastcall CharacterSet::Bitmap()
{
    if (m_Bitmap == nullptr && FileSystem::File::Exists(m_File))
    {
        // load the file
        m_Bitmap = make_unique<TBitmap>();
        m_Bitmap->LoadFromFile(m_File);
        // make the bottom right pixel the transparent pixel
        TBitmapData bmpd;
        if (m_Bitmap->Map(TMapAccess::ReadWrite, bmpd))
        {
            auto transparent = TAlphaColor(0x00000000);
            auto color2match = bmpd.GetPixel(0,0);
            for (auto y = 0; y < bmpd.Height; y++)
            {
                auto sl = bmpd.GetScanline(y);
                for (auto x = 0; x < bmpd.Height; x++)
                {
                    if (((TAlphaColor*)sl)[x] == color2match)
                    {
                        ((TAlphaColor*)sl)[x] = transparent;
                    }
                }
            }
            m_Bitmap->Unmap(bmpd);
        }
    }
    return m_Bitmap.get();
}
//---------------------------------------------------------------------------
} // project namepsace
//---------------------------------------------------------------------------
