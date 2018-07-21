//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.Math.hpp>
#include "TileEditor.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TileEditor::TileEditor(TImage* view, const TSize& size, bool usesGridTile, bool usesGridRoom, int border)
: m_View(view)
, m_Size(size)
, m_UsesGridTile(usesGridTile)
, m_UsesGridRoom(usesGridRoom)
, m_ShowGridTile(false)
, m_ShowGridRoom(usesGridRoom)
, m_Border(border)
, m_Scale(2)
, m_MouseMode(mmTool)
, m_MousePanning(false)
, m_MouseButtonDown(false)
, m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
{
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    m_Content = std::make_unique<TBitmap>();
    m_Content->PixelFormat = pf32bit;
    auto cw = wi.Width  * m_TileSize.cx * 16;   // 16 rooms across
    auto ch = wi.Height * m_TileSize.cy * 16;   // 16 rooms down
    m_Content->Width  = (m_Border * 2) + cw;    // 16 x 16 rooms
    m_Content->Height = (m_Border * 2) + ch;

    Clear();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Clear()
{
    PatBlt(m_Content->Canvas->Handle, 0, 0, m_Content->Width, m_Content->Height, BLACKNESS);
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ValidatePosition()
{
    m_Position.X = Max(0, Min(m_Content->Width  - (m_View->Width  / m_Scale), m_Position.X));
    m_Position.Y = Max(0, Min(m_Content->Height - (m_View->Height / m_Scale), m_Position.Y));
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::GetCursorPt(int X, int Y) const
{
    auto x = (X / m_Scale) - m_Border + m_Position.X;
    auto y = (Y / m_Scale) - m_Border + m_Position.Y;
    return TPoint(x,y);
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (!m_MousePanning && Button == mbLeft && m_PrevMouseMode == mmGroupSelect && !Shift.Contains(ssCtrl) && !Shift.Contains(ssShift))
    {
        UnselectAll();
        m_MouseMode = mmTool;
    }
    if (Shift.Contains(ssShift) && Button == mbLeft)
    {
        m_MousePanning = true;
        Screen->Cursor =  crSizeAll;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
    }
    else if (m_MouseMode == mmTool && m_Mode == temSelect && Shift.Contains(ssCtrl) && Button == mbLeft)
    {
        // start group selecting the entities
        m_MouseMode = mmGroupSelect;
        m_GroupSelectS = GetCursorPt(X, Y);
        m_GroupSelectE = m_GroupSelectS;
        m_GroupSelectS.X = m_GroupSelectS.X - (m_GroupSelectS.X % m_TileSize.cx);
        m_GroupSelectS.Y = m_GroupSelectS.Y - (m_GroupSelectS.Y % m_TileSize.cy);
        m_GroupSelectE.X = m_GroupSelectE.X - (m_GroupSelectE.X % m_TileSize.cx) + m_TileSize.cx;
        m_GroupSelectE.Y = m_GroupSelectE.Y - (m_GroupSelectE.Y % m_TileSize.cy) + m_TileSize.cy;
    }
    m_MouseButtonDown = Button == mbLeft;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMove(TShiftState Shift, int X, int Y)
{
//    if (!m_MouseButtonDown)
//        return;
    if (m_MousePanning)
    {
        m_Position.X -= (X - m_LastMouse.X) / m_Scale;
        m_Position.Y -= (Y - m_LastMouse.Y) / m_Scale;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
        Refresh();
    }
    else
    {
        switch (m_MouseMode)
        {
            case mmTool:
                if (m_Mode == temSelect && m_PrevMouseMode != mmGroupSelect)
                {
                    UnselectAll();
                    // find an object that intersects the mouse
                    auto pt = GetCursorPt(X, Y);
                    // select sprites or objects first
                    auto selected = false;
                    for (auto& e : m_Entities)
                    {
                        if (e.Image->ImageType != itTile)
                        {
                            auto ex = e.Pt.x * m_TileSize.cx;
                            auto ey = e.Pt.y * m_TileSize.cy;
                            e.Selected = (ex <= pt.X && pt.X <= ex + e.Image->Width && ey <= pt.Y && pt.Y <= ey + e.Image->Height);
                            selected |= e.Selected;
                        }
                    }
                    if (!selected)
                    {
                        // if nothing selected, select a tile/block
                        for (auto& e : m_Entities)
                        {
                            if (e.Image->ImageType == itTile)
                            {
                                auto ex = e.Pt.x * m_TileSize.cx;
                                auto ey = e.Pt.y * m_TileSize.cy;
                                e.Selected = (ex <= pt.X && pt.X < ex + e.Image->Width && ey <= pt.Y && pt.Y < ey + e.Image->Height);
                            }
                        }
                    }
                    Refresh();
                }
                break;
            case mmGroupSelect:
                {
                    m_GroupSelectE = GetCursorPt(X, Y);
                    m_GroupSelectE.X = m_GroupSelectE.X - (m_GroupSelectE.X % m_TileSize.cx) + m_TileSize.cx;
                    m_GroupSelectE.Y = m_GroupSelectE.Y - (m_GroupSelectE.Y % m_TileSize.cy) + m_TileSize.cy;
                    auto minX = Min((int)m_GroupSelectS.X, (int)m_GroupSelectE.X);
                    auto maxX = Max((int)m_GroupSelectS.X, (int)m_GroupSelectE.X);
                    auto minY = Min((int)m_GroupSelectS.Y, (int)m_GroupSelectE.Y);
                    auto maxY = Max((int)m_GroupSelectS.Y, (int)m_GroupSelectE.Y);
                    if (minX != maxX && minY != maxY)
                    {
                        for (auto& e : m_Entities)
                        {
                            auto ex = e.Pt.x * m_TileSize.cx;
                            auto ey = e.Pt.y * m_TileSize.cy;
                            e.Selected = (minX <= ex && ex + e.Image->Width <= maxX && minY <= ey && ey + e.Image->Height <= maxY);
                        }
                    }
                    Refresh();
                }
                break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_MouseButtonDown = false;
    if (m_MousePanning)
    {
        m_MousePanning = false;
    }
    else
    {
        m_PrevMouseMode = m_MouseMode;
        m_MouseMode = mmTool;
        Refresh();
    }
    Screen->Cursor =  crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetGridTile(bool value)
{
    m_ShowGridTile = value;
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetGridRoom(bool value)
{
    m_ShowGridRoom = value;
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetSize(TSize size)
{
    m_Size = size;
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UpdateMap()
{
    // update the content
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawGrids() const
{
    const auto& gm = m_GraphicsMode;
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    int scalarX = gm.ScalarX;
    int scalarY = gm.ScalarY;
    auto Canvas = m_View->Picture->Bitmap->Canvas;
    Canvas->Pen->Style = psSolid;
    auto bx = m_Border * m_Scale;

    auto xs =  (m_Border - m_Position.X) * m_Scale;
    auto xe = xs + ((m_Content->Width  - (m_Border * 2)) * m_Scale);
    auto ys =  (m_Border - m_Position.Y) * m_Scale;
    auto ye = ys + ((m_Content->Height - (m_Border * 2)) * m_Scale);
    if (m_UsesGridTile && m_ShowGridTile)
    {
        auto sx = m_TileSize.cx * m_Scale * scalarX;
        Canvas->Pen->Color = (TColor)0x00004080;
        for (auto x = xs; x <= xe; x += sx)
        {
            Canvas->MoveTo(x, ys);
            Canvas->LineTo(x, ye);
        }
        auto sy = m_TileSize.cy * m_Scale * scalarY;
        for (auto y = ys; y <= ye; y += sy)
        {
            Canvas->MoveTo(xs, y);
            Canvas->LineTo(xe, y);
        }
    }
    if (m_UsesGridRoom && m_ShowGridRoom)
    {
        Canvas->Pen->Color = (TColor)0x0048BAF7;
        auto rx = wi.Width  * m_TileSize.cx * scalarX * m_Scale;
        auto ry = wi.Height * m_TileSize.cy * scalarY * m_Scale;
        for (auto x = xs; x <= xe; x += rx)
        {
            Canvas->MoveTo(x, ys);
            Canvas->LineTo(x, ye);
        }
        for (auto y = ys; y <= ye; y += ry)
        {
            Canvas->MoveTo(xs    , y);
            Canvas->LineTo(xe + 1, y);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawGroupSelect() const
{
    if (m_MouseMode == mmGroupSelect)
    {
        auto xs =  (m_Border - m_Position.X) * m_Scale;
        auto ys =  (m_Border - m_Position.Y) * m_Scale;
        auto Canvas = m_View->Picture->Bitmap->Canvas;
        Canvas->Pen->Style = psDash;
        Canvas->Pen->Color = clWhite;
        Canvas->Brush->Color = clBlack;
        Canvas->MoveTo(xs + m_GroupSelectS.X * m_Scale, ys + m_GroupSelectS.Y * m_Scale);
        Canvas->LineTo(xs + m_GroupSelectE.X * m_Scale, ys + m_GroupSelectS.Y * m_Scale);
        Canvas->LineTo(xs + m_GroupSelectE.X * m_Scale, ys + m_GroupSelectE.Y * m_Scale);
        Canvas->LineTo(xs + m_GroupSelectS.X * m_Scale, ys + m_GroupSelectE.Y * m_Scale);
        Canvas->LineTo(xs + m_GroupSelectS.X * m_Scale, ys + m_GroupSelectS.Y * m_Scale);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawMap()
{
    for (auto& entity : m_Entities)
    {
        if (entity.Dirty)
        {
            TPoint pt(entity.Pt);
            pt.x *= m_TileSize.cx;
            pt.y *= m_TileSize.cy;
            pt.x += m_Border;
            pt.y += m_Border;
            m_ImageMap[entity.Id]->Draw(pt, m_Content.get(), entity.Selected);
            entity.Clean();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Refresh()
{
    ValidatePosition();
    if (m_View->Width != m_View->Picture->Bitmap->Width || m_View->Height != m_View->Picture->Bitmap->Height)
    {
        m_View->Picture->Bitmap->Width = m_View->Width;
        m_View->Picture->Bitmap->Height = m_View->Height;
    }

    auto vw = m_View->Width;
    auto vh = m_View->Height;
    auto cw = (int)(vw / m_Scale);
    auto ch = (int)(vh / m_Scale);
    auto cx = m_Position.X;
    auto cy = m_Position.Y;
    // draw the entities
    DrawMap();
    // show the map
    StretchBlt(m_View->Picture->Bitmap->Canvas->Handle, 0, 0, vw, vh, m_Content->Canvas->Handle, cx, cy, cw, ch, SRCCOPY);
    DrawGrids();
    DrawGroupSelect();
    m_View->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::RefreshImages()
{
    m_ImageMap.clear();
    for (const auto& entity : m_Entities)
    {
        if (m_ImageMap.count(entity.Id) == 0)
        {
            // add the image to the map
            m_ImageMap[entity.Id] = std::make_unique<Agdx::Image>(entity.Image, m_GraphicsMode);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetEntities(const EntityList& entities)
{
    m_Entities = entities;
    for (auto& e : m_Entities) e.Dirty = true;
    // render all the images
    RefreshImages();
}
//---------------------------------------------------------------------------
const EntityList& __fastcall TileEditor::GetEntities() const
{
    return m_Entities;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Get(const TRect& rect, EntityList& entities) const
{
    // get all entities that start within the rect
    std::copy_if(m_Entities.begin(), m_Entities.end(), entities.begin(), [rect](const Entity e)
    {
        return rect.Contains(e.Pt);
    });
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Add(EntityList& entities)
{
    m_Entities.insert(m_Entities.end(), entities.begin(), entities.end());
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Remove(const TRect& rect)
{
    // remove all entities with a start pt inside the rect
    m_Entities.erase(std::remove_if(m_Entities.begin(), m_Entities.end(), [rect](const Entity& e)
    {
        return rect.Contains(e.Pt);
    }), m_Entities.end());
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UnselectAll()
{
    for (auto& e : m_Entities) e.Selected = false;
}
//---------------------------------------------------------------------------

