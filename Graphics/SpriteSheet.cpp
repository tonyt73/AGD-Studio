//---------------------------------------------------------------------------
#include "Arcadium.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <System.RegularExpressions.hpp>
#include "FileSystem\File.h"
#include "FileSystem\Path.h"
#include "SpriteSheet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
namespace Graphics
{
//---------------------------------------------------------------------------
std::unique_ptr<TBitmap> SpriteSheet::m_Checkerboard = nullptr;
//---------------------------------------------------------------------------
struct Layout
{
    Layout(float width, float height)
    : Width(width)
    , Height(height)
    {
        Points.clear();
    }

    float               Width;
    float               Height;
    std::list<TPointF>  Points;
};
typedef std::vector<Layout> Layouts;
// WARNING: THIS MIGHT CRASH ON ANDROID/IOS
static Layouts g_Layouts;
const float m_Scale = 10.f;
//---------------------------------------------------------------------------
__fastcall SpriteSheet::SpriteSheet()
: m_Width(0)
, m_Height(0)
, m_Ways(0)
, m_Direction(swAll)
, m_Frames(0)
, m_HasShadow(false)
, m_SpriteSheet(nullptr)
, m_ShadowSheet(nullptr)
, m_View(nullptr)
{
    InitialiseLayouts();
    m_View = make_unique<TBitmap>();
    m_Background = make_unique<TBitmap>();
}
//---------------------------------------------------------------------------
void __fastcall SpriteSheet::InitialiseLayouts()
{
    if (g_Layouts.size() == 0)
    {
        auto w01 = Layout(1.0f,  1.0f);
        w01.Points.push_back(TPointF(0.0,0.0));
        auto w2v = Layout(1.0f,  3.0f);
        w2v.Points.push_back(TPointF(0.0,0.0));
        w2v.Points.push_back(TPointF(0.0,2.0));
        auto w2h = Layout(3.0f,  1.0f);
        w2h.Points.push_back(TPointF(0.0,0.0));
        w2h.Points.push_back(TPointF(2.0,0.0));
        auto w3v = Layout(1.0f,  4.0f);
        w3v.Points.push_back(TPointF(0.0,0.0));
        w3v.Points.push_back(TPointF(1.5,0.0));
        w3v.Points.push_back(TPointF(3.0,0.0));
        auto w3h = Layout(4.0f,  1.0f);
        w3h.Points.push_back(TPointF(0.0,0.0));
        w3h.Points.push_back(TPointF(0.0,1.5));
        w3h.Points.push_back(TPointF(0.0,3.0));
        auto w04 = Layout(4.0f,  4.0f);
        w04.Points.push_back(TPointF(1.5,0.0));
        w04.Points.push_back(TPointF(3.0,1.5));
        w04.Points.push_back(TPointF(1.5,3.0));
        w04.Points.push_back(TPointF(0.0,1.5));
        auto w08 = Layout(4.0f,  4.0f);
        w08.Points.push_back(TPointF(1.5,0.0));
        w08.Points.push_back(TPointF(3.0,0.0));
        w08.Points.push_back(TPointF(3.0,1.5));
        w08.Points.push_back(TPointF(3.0,3.0));
        w08.Points.push_back(TPointF(1.5,3.0));
        w08.Points.push_back(TPointF(0.0,3.0));
        w08.Points.push_back(TPointF(0.0,1.5));
        w08.Points.push_back(TPointF(0.0,0.0));
        auto w10 = Layout(2.5f, 12.0f);
        // TODO: Add 10 way layout support
        auto w16 = Layout(7.0f,  7.0f);
        w16.Points.push_back(TPointF(3.0,0.0));
        w16.Points.push_back(TPointF(4.5,0.0));
        w16.Points.push_back(TPointF(6.0,0.0));
        w16.Points.push_back(TPointF(6.0,1.5));
        w16.Points.push_back(TPointF(6.0,3.0));
        w16.Points.push_back(TPointF(6.0,4.5));
        w16.Points.push_back(TPointF(6.0,6.0));
        w16.Points.push_back(TPointF(4.5,6.0));
        w16.Points.push_back(TPointF(3.0,6.0));
        w16.Points.push_back(TPointF(1.5,6.0));
        w16.Points.push_back(TPointF(0.0,6.0));
        w16.Points.push_back(TPointF(0.0,4.5));
        w16.Points.push_back(TPointF(0.0,3.0));
        w16.Points.push_back(TPointF(0.0,1.5));
        w16.Points.push_back(TPointF(0.0,0.0));
        w16.Points.push_back(TPointF(1.5,0.0));

        g_Layouts.push_back(w01);
        g_Layouts.push_back(w2v);
        g_Layouts.push_back(w2h);
        g_Layouts.push_back(w3v);
        g_Layouts.push_back(w3h);
        g_Layouts.push_back(w04);
        g_Layouts.push_back(w08);
        g_Layouts.push_back(w10);
        g_Layouts.push_back(w16);
    }
}
//---------------------------------------------------------------------------
void __fastcall SpriteSheet::Draw(TBitmap* bitmap, int way, int frame, float x, float y)
{
    if (bitmap != nullptr && 0 <= way && way < m_Ways && 0 <= frame && frame < m_Frames)
    {
        if (bitmap->Canvas->BeginScene())
        {
            bitmap->Canvas->DrawBitmap(
                m_SpriteSheet.get(),
                TRectF(frame * m_Width, way * m_Height, frame * m_Width + m_Width, way * m_Height + m_Height),
                TRectF(x, y, x + m_Width, y + m_Height),
                1.0f, true);
            bitmap->Canvas->EndScene();
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall SpriteSheet::GetLayoutIndex() const
{
    int layoutIndex = 0;
    switch (m_Ways)
    {
        case  2: layoutIndex = m_Direction == swLeftRight ? 1 : 2;  break;
        case  3: layoutIndex = m_Direction == swLeftRight ? 3 : 4;  break;
        case  4: layoutIndex = 5;                               break;
        case  8: layoutIndex = 6;                               break;
        case 10: layoutIndex = 7;                               break;
        case 16: layoutIndex = 8;                               break;
        default:                                                break;
    }
    return layoutIndex;
}
//---------------------------------------------------------------------------
TSize __fastcall SpriteSheet::GetLayoutSize() const
{
    TSize size;
    auto layoutIndex = GetLayoutIndex();
    size.cx = g_Layouts[layoutIndex].Width  * m_Width;
    size.cy = g_Layouts[layoutIndex].Height * m_Height;

    return size;
}
//---------------------------------------------------------------------------
TBitmap* __fastcall SpriteSheet::LayoutView(int frame, bool loop)
{
    m_View->Assign(m_Background.get());
    if (0 <= frame && frame < m_Frames)
    {
            auto size = GetLayoutSize();
            if (m_View->Canvas->BeginScene())
            {
                auto li = GetLayoutIndex();
                const auto& points = g_Layouts[li].Points;
                auto way = 0;
                for (const auto& pt : points)
                {
                    if (m_HasShadow)
                    {
                        m_View->Canvas->DrawBitmap(
                            m_ShadowSheet.get(),
                            TRectF(frame * m_Width, way * m_Height, frame * m_Width + m_Width, way * m_Height + m_Height),
                            TRectF(m_Scale * m_Width * pt.x, m_Scale * m_Height * pt.y, (m_Width * pt.x + m_Width) * m_Scale, (m_Height * pt.y + m_Height) * m_Scale),
                            1.0f, true);
                    }
                    m_View->Canvas->DrawBitmap(
                        m_SpriteSheet.get(),
                        TRectF(frame * m_Width, way * m_Height, frame * m_Width + m_Width, way * m_Height + m_Height),
                        TRectF(m_Scale * m_Width * pt.x, m_Scale * m_Height * pt.y, (m_Width * pt.x + m_Width) * m_Scale, (m_Height * pt.y + m_Height) * m_Scale),
                        1.0f, true);
                    way++;
                }
                m_View->Canvas->EndScene();
            }
    }
    return m_View.get();
}
//---------------------------------------------------------------------------
bool __fastcall SpriteSheet::ParseFilename(const String& pngFile)
{
    auto file = FileSystem::File::NameWithoutExtension(pngFile);
    auto uc = file.LastDelimiter("_");
    if (uc > 0)
    {
        auto params = file.SubString(uc + 1, file.Length() - uc).LowerCase();
        auto wh = params.Pos("wh");
        auto wv = params.Pos("wh");
        auto w  = params.Pos("w");
        m_Name = pngFile;

        if (w == 0)
        {
            return false;
        }
        m_Frames = StrToIntDef(params.SubString(w + 1, params.Length()), 0);
        m_Ways = StrToInt(params.SubString(1, w - 1));
        if ((m_Ways == 2 || m_Ways == 3) && (wh > 0 || wv > 0))
        {
            m_Frames = StrToIntDef(params.SubString(w + 2, params.Length()), 0);
            m_Direction = wh > 0 ? swLeftRight : swUpDown;
        }

        // TODO: Add 10w support back
        if (m_Name.Trim() != "" &&
           (m_Ways == 1 || m_Ways == 2 || m_Ways == 3 || m_Ways == 4 || m_Ways == 8 || /*m_Ways == 10 ||*/ m_Ways == 16) &&
           (0 < m_Frames && m_Frames < 32))
        {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall SpriteSheet::Load(const String& pngFile)
{
    bool result = false;
    if (FileSystem::File::Exists(pngFile))
    {
        if (ParseFilename(pngFile))
        {
            result = true;
            m_SpriteSheet = make_unique<TBitmap>();
            m_SpriteSheet->LoadFromFile(pngFile);
            auto filename = FileSystem::File::NameWithoutExtension(pngFile);
            auto shadowFile = FileSystem::File::PathOf(pngFile) + "/" + filename + "s.png";
            m_HasShadow = false;
            if (FileSystem::File::Exists(shadowFile))
            {
                m_HasShadow = true;
                m_ShadowSheet = make_unique<TBitmap>();
                m_ShadowSheet->LoadFromFile(shadowFile);
                // sprite sheet and shadow sheet must be same size
                result &= (m_SpriteSheet->Width == m_ShadowSheet->Width && m_SpriteSheet->Height == m_ShadowSheet->Height);
            }
            // work out sprite width/height
            m_Width = m_SpriteSheet.get()->Width / m_Frames;
            m_Height = m_SpriteSheet.get()->Height / m_Ways;
            // must be multiple of 8
            result &= (m_Width % 8 == 0 && m_Height % 8 == 0);
            if (result)
            {
                if (m_Checkerboard == nullptr)
                {
                    // create the checkerboard background
                    m_Checkerboard = make_unique<TBitmap>();
                    auto file = FileSystem::File::Combine(FileSystem::Path::Common, "Helpers");
                    file = FileSystem::File::Combine(file, "checkerboard.bmp");
                    m_Checkerboard->LoadFromFile(file);
                }
                auto size = GetLayoutSize();
                m_Background->Width = size.cx * m_Scale;
                m_Background->Height = size.cy * m_Scale;
                m_Background->Clear(TAlphaColorRec::Null);
                if (m_Background->Canvas->BeginScene())
                {
                    auto li = GetLayoutIndex();
                    const auto& points = g_Layouts[li].Points;
                    auto count = points.size();
                    for (const auto& pt : points)
                    {
                        m_Background->Canvas->DrawBitmap(
                            m_Checkerboard.get(),
                            TRectF(0, 0, m_Width, m_Height),
                            TRectF(m_Scale * m_Width * pt.x, m_Scale * m_Height * pt.y, (m_Width * pt.x + m_Width) * m_Scale, (m_Height * pt.y + m_Height) * m_Scale),
                            1.0f, true);
                    }
                    m_Background->Canvas->EndScene();
                }
                String direction = "";
                if (m_Ways == 2 || m_Ways == 3) direction = m_Direction == swLeftRight ? " Horizontal" : " Vertical";
                m_Description = IntToStr(m_Ways) + "-WAY" + direction + " [" + IntToStr(m_Width) + "x" + IntToStr(m_Height) + (m_HasShadow ? "] + SHADOW" : "]");
            }
        }
    }
    if (!result)
    {
        m_SpriteSheet = nullptr;
        m_ShadowSheet = nullptr;
    }
    return result;
}
//---------------------------------------------------------------------------
} // graphics namespace
//---------------------------------------------------------------------------

