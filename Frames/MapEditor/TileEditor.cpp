//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.Math.hpp>
#include "TileEditor.h"
#include "Project/DocumentManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TileEditor::TileEditor(TImage* const view, const TSize& rooms, bool usesGridTile, bool usesGridRoom, int border, bool readOnly)
: m_View(view)
, m_Rooms(rooms)
, m_UsesGridTile(usesGridTile)
, m_UsesGridRoom(usesGridRoom)
, m_ShowGridTile(false)
, m_ShowGridRoom(usesGridRoom)
, m_Border(border)
, m_ScaleFactor(2)
, m_MouseMode(mmTool)
, m_MousePanning(false)
, m_SelectionMove(false)
, m_ForceMapDraw(false)
, m_SelectionCount(0)
, m_Tile0Window(nullptr)
, m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_ReadOnly(readOnly)
{
    Scale = m_ScaleFactor;

    CreateViewBitmap();
    Clear();

    ::Messaging::Bus::Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall TileEditor::~TileEditor()
{
    ::Messaging::Bus::Unsubscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::CreateViewBitmap()
{
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    m_WindowSize.cx = wi.Width;
    m_WindowSize.cy = wi.Height;
    m_Content = std::make_unique<TBitmap>();
    m_Content->PixelFormat = pf32bit;
    m_ContentSize.cx = wi.Width  * m_TileSize.cx * m_Rooms.cx + (m_BorderScaled.x * 2);
    m_ContentSize.cy = wi.Height * m_TileSize.cy * m_Rooms.cy + (m_BorderScaled.y * 2);
    m_Content->Width  = Screen->Width;
    m_Content->Height = Screen->Height;
    PatBlt(m_Content->Canvas->Handle, 0, 0, m_Content->Width, m_Content->Height, BLACKNESS);
    m_ForceMapDraw = true;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnEvent(const Event& event)
{
    if (event.Id == "image.modified" || event.Id == "document.added" || event.Id == "document.removed")
    {
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Clear()
{
    PatBlt(m_Content->Canvas->Handle, m_BorderScaled.x, m_BorderScaled.y, m_Content->Width, m_Content->Height, BLACKNESS);
    if (m_Tile0Window)
    {
        // clear the map using tile 0's
        const auto& wi = theDocumentManager.ProjectConfig()->Window;
        auto cw = wi.Width  * m_TileSize.cx;
        auto ch = wi.Height * m_TileSize.cy;
        for (auto y = m_BorderScaled.y; y < m_ContentSize.cy - (m_BorderScaled.y * 2); y += m_Tile0Window->Height)
        {
            for (auto x = m_BorderScaled.x; x < m_ContentSize.cx - (m_BorderScaled.x * 2); x += m_Tile0Window->Width)
            {
                BitBlt(m_Content->Canvas->Handle, x, y, m_Tile0Window->Width, m_Tile0Window->Height, m_Tile0Window->Canvas->Handle, 0, 0, SRCCOPY);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ValidatePosition()
{
    m_PositionMS.X = max(0, (int)min(m_ContentSize.cx - (int)(m_View->Width  / m_Scale.x), m_PositionMS.X));
    m_PositionMS.Y = max(0, (int)min(m_ContentSize.cy - (int)(m_View->Height / m_Scale.y), m_PositionMS.Y));
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::MapToView(const TPoint& pt) const
{
    auto x = m_Border + ((pt.x - m_PositionMS.X) * m_Scale.x);
    auto y = m_Border + ((pt.y - m_PositionMS.Y) * m_Scale.y);
    return TPoint(x, y);
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::ViewToMap(int X, int Y) const
{
    auto pt = TPoint(X / m_Scale.x, Y / m_Scale.y);
    auto bt = TPoint(m_BorderScaled.x, m_BorderScaled.y);
    return (m_PositionMS + (pt - bt));
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_ReadOnly && !Shift.Contains(ssCtrl) && !Shift.Contains(ssShift) && Button == mbLeft)
    {
        // work out the room number
        const auto& wi = theDocumentManager.ProjectConfig()->Window;
        auto pt = ViewToMap(X, Y);
        pt.x /= m_TileSize.cx * wi.Width;
        pt.y /= m_TileSize.cy * wi.Height;
        if (Shift.Contains(ssAlt))
        {
            StartRoom = pt;
        }
        else
        {
            SelectRoom(TSize(pt.x, pt.y));
        }
    }
    else if (m_SelectionCount > 0 && Button == mbLeft && !Shift.Contains(ssCtrl) && !Shift.Contains(ssShift))
    {
        if (m_SelectionCount == 1 && FOnEntitySelected != nullptr)
        {
            SelectedEntity = m_SingleSelect.Id;
            FOnEntitySelected(m_SingleSelect);
        }
        m_SelectionMove = true;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
    }
    else if (!m_MousePanning && Button == mbLeft && m_PrevMouseMode == mmGroupSelect && !Shift.Contains(ssCtrl) && !Shift.Contains(ssShift))
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
        m_SelectionCount = 0;
        m_MouseMode = mmGroupSelect;
        m_GroupSelectSrtMS = ViewToMap(X, Y);
        m_GroupSelectEndMS = m_GroupSelectSrtMS;
        m_GroupSelectSrtMS.X = Snap(m_GroupSelectSrtMS.X, m_TileSize.cx);
        m_GroupSelectSrtMS.Y = Snap(m_GroupSelectSrtMS.Y, m_TileSize.cy);
        m_GroupSelectEndMS.X = Snap(m_GroupSelectEndMS.X, m_TileSize.cx);
        m_GroupSelectEndMS.Y = Snap(m_GroupSelectEndMS.Y, m_TileSize.cy);
    }
    else if (Button == mbLeft && ShowStartRoom && !ShowSelectedRoom && Shift.Contains(ssAlt))
    {
        // work out the room number
        const auto& wi = theDocumentManager.ProjectConfig()->Window;
        auto pt = ViewToMap(X, Y);
        pt.x /= m_TileSize.cx * wi.Width;
        pt.y /= m_TileSize.cy * wi.Height;
        StartRoom = pt;
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMove(TShiftState Shift, int X, int Y)
{
    auto dPt = TPoint((X - m_LastMouse.X) / m_Scale.x, (Y - m_LastMouse.Y) / m_Scale.y);
    if (m_MousePanning)
    {
        m_PositionMS -= dPt;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
        Refresh();
    }
    else if (m_SelectionMove)
    {
        auto outOfBounds = false;
        for (auto& e : m_Entities)
        {
            if (e.Selected)
            {
                auto pt = e.Pt - e.DragPt + dPt;
                if (pt.x < 0 || pt.y < 0 || (pt.x + m_TileSize.cx) >= (m_ContentSize.cx - (m_BorderScaled.x * 2)) || (pt.y + m_TileSize.cy) >= (m_ContentSize.cy - (m_BorderScaled.y * 2)))
                {
                    outOfBounds = true;
                    break;
                }
            }
        }
        if (!outOfBounds)
        {
            for (auto& e : m_Entities)
            {
                if (e.Selected)
                {
                    e.DragPt = dPt;
                }
            }
            UpdateMap();
        }
    }
    else if (!m_ReadOnly)
    {
        switch (m_MouseMode)
        {
            case mmTool:
                if (m_Mode == temSelect && m_PrevMouseMode != mmGroupSelect)
                {
                    UnselectAll();
                    // find an object that intersects the mouse
                    auto pt = ViewToMap(X, Y);
                    // select sprites or objects first
                    for (auto& e : m_Entities)
                    {
                        if (e.Image->ImageType != itTile)
                        {
                            auto ex = e.Pt.x;
                            auto ey = e.Pt.y;
                            e.Selected = (ex <= pt.X && pt.X <= ex + e.Image->Width && ey <= pt.Y && pt.Y <= ey + e.Image->Height);
                            m_SelectionCount += e.Selected ? 1 : 0;
                            if (e.Selected)
                            {
                                m_SingleSelect = e;
                            }
                        }
                    }
                    if (!m_SelectionCount)
                    {
                        // if nothing selected, select a tile/block
                        for (auto& e : m_Entities)
                        {
                            if (e.Image->ImageType == itTile)
                            {
                                auto ex = e.Pt.x;
                                auto ey = e.Pt.y;
                                e.Selected = (ex <= pt.X && pt.X < ex + e.Image->Width && ey <= pt.Y && pt.Y < ey + e.Image->Height);
                                m_SelectionCount += e.Selected ? 1 : 0;
                                if (e.Selected)
                                {
                                    m_SingleSelect = e;
                                    break;
                                }
                            }
                        }
                    }
                    if (Shift.Contains(ssMiddle))
                    {
                        DeleteSelection();
                    }
                    Refresh();
                }
                break;
            case mmGroupSelect:
                {
                    m_GroupSelectEndMS = ViewToMap(X, Y);
                    m_GroupSelectEndMS.X = Snap(m_GroupSelectEndMS.X, m_TileSize.cx) + m_TileSize.cx;
                    m_GroupSelectEndMS.Y = Snap(m_GroupSelectEndMS.Y, m_TileSize.cy) + m_TileSize.cy;
                    auto minX = min(m_GroupSelectSrtMS.X, m_GroupSelectEndMS.X);
                    auto maxX = max(m_GroupSelectSrtMS.X, m_GroupSelectEndMS.X);
                    auto minY = min(m_GroupSelectSrtMS.Y, m_GroupSelectEndMS.Y);
                    auto maxY = max(m_GroupSelectSrtMS.Y, m_GroupSelectEndMS.Y);
                    if (minX != maxX && minY != maxY)
                    {
                        for (auto& e : m_Entities)
                        {
                            auto ex = e.Pt.x;
                            auto ey = e.Pt.y;
                            e.Selected = (minX <= ex && ex + e.Image->Width <= maxX && minY <= ey && ey + e.Image->Height <= maxY);
                            m_SelectionCount += e.Selected ? 1 : 0;
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
    if (m_SelectionMove)
    {
        m_SelectionMove = false;
        // snap the selected items to the grid
        for (auto& e : m_Entities)
        {
            if (e.Selected)
            {
                // TODO: Some machines with hardware sprites might not have a grid limitation
                //       Should add this to the machine config and only apply if needed
                e.Pt = TPoint(Snap(e.Pt.X, m_TileSize.cx), Snap(e.Pt.Y, m_TileSize.cy));
                e.DragPt = TPoint();
            }
        }
        UpdateMap();
    }
    else if (m_MousePanning)
    {
        m_MousePanning = false;
    }
    else if (!m_ReadOnly)
    {
        if (Button == mbLeft && Shift.Contains(ssCtrl) && m_SelectionCount == 0)
        {
            UnselectAll();
        }
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
void __fastcall TileEditor::SetRooms(TSize rooms)
{
    m_Entities.clear();
    m_Rooms = rooms;
    CreateViewBitmap();
    Clear();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetTile0Id(unsigned int id)
{
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    m_Tile0Window = std::make_unique<TBitmap>();
    m_Tile0Window->PixelFormat = pf32bit;
    m_Tile0Window->Width = wi.Width * m_TileSize.cx;
    m_Tile0Window->Height = wi.Height * m_TileSize.cy;
    TPoint pt;
    auto tile0 = dynamic_cast<ImageDocument*>(theDocumentManager.Get(id));
    if (tile0)
    {
        auto image0 = std::make_unique<Agdx::Image>(tile0, m_GraphicsMode);
        for (auto y = 0; y < wi.Height; y++)
        {
            for (auto x = 0; x < wi.Width; x++)
            {
                pt.X = x * m_TileSize.cx;
                pt.Y = y * m_TileSize.cy;
                image0->Draw(pt, m_Tile0Window.get());
            }
        }
    }
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetSelectedEntity(unsigned int id)
{
	m_SelectedEntity = id;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetScale(float scale)
{
    const auto& gm = m_GraphicsMode;
    m_ScaleFactor = scale;
    m_Scale.x = scale * gm.ScalarX;
    m_Scale.y = scale * gm.ScalarY;
    m_BorderScaled.x = m_Border / m_Scale.x;
    m_BorderScaled.y = m_Border / m_Scale.y;
    CreateViewBitmap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetReadOnly(bool state)
{
    m_ReadOnly = state;
    if (m_ReadOnly)
    {
        m_UsesGridRoom = true;
        m_ShowGridRoom = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetShowSelectedRoom(bool state)
{
    m_ShowSelectedRoom = state;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetShowStartRoom(bool state)
{
    m_ShowStartRoom = state;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetStartRoom(TPoint location)
{
    if ((location.x != m_StartRoom.x || location.y != m_StartRoom.y) && 0 <= location.x && location.y < m_Rooms.cx && 0 <= location.y && location.y < m_Rooms.cy)
    {
        m_StartRoom = location;
        UpdateMap();
        Messaging::Bus::Publish<StartRoomSet>(StartRoomSet(m_StartRoom));
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UpdateMap()
{
    // update the content
    m_ForceMapDraw = true;
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawGrids() const
{
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    auto Canvas = m_View->Picture->Bitmap->Canvas;
    Canvas->Pen->Style = psSolid;

    auto xs =  m_Border - (m_PositionMS.X * m_Scale.x);
    auto xe = xs + ((m_ContentSize.cx - (m_BorderScaled.x * 2)) * m_Scale.x);
    auto ys =  m_Border - (m_PositionMS.Y * m_Scale.y);
    auto ye = ys + ((m_ContentSize.cy - (m_BorderScaled.y * 2)) * m_Scale.y);
    if (m_UsesGridTile && m_ShowGridTile)
    {
        auto sx = m_TileSize.cx * m_Scale.x;
        Canvas->Pen->Color = (TColor)0x00004080;
        for (auto x = xs; x <= xe; x += sx)
        {
            Canvas->MoveTo(x, ys);
            Canvas->LineTo(x, ye);
        }
        auto sy = m_TileSize.cy * m_Scale.y;
        for (auto y = ys; y <= ye; y += sy)
        {
            Canvas->MoveTo(xs, y);
            Canvas->LineTo(xe, y);
        }
    }
    if (m_UsesGridRoom && m_ShowGridRoom)
    {
        Canvas->Pen->Color = (TColor)0x0048BAF7;
        auto rx = wi.Width  * m_TileSize.cx * m_Scale.x;
        auto ry = wi.Height * m_TileSize.cy * m_Scale.y;
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
        auto Canvas = m_View->Picture->Bitmap->Canvas;
        Canvas->Pen->Style = psDot;
        Canvas->Pen->Color = clWhite;
        Canvas->Brush->Color = clBlack;
        auto gs = MapToView(m_GroupSelectSrtMS);
        auto ge = MapToView(m_GroupSelectEndMS);
        Canvas->MoveTo(gs.x, gs.y);
        Canvas->LineTo(ge.x, gs.y);
        Canvas->LineTo(ge.x, ge.y);
        Canvas->LineTo(gs.x, ge.y);
        Canvas->LineTo(gs.x, gs.y);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawEntities(int filters)
{
    for (auto& entity : m_Entities)
    {
        bool draw  = (filters & edfForce) == edfForce;
             draw |= ((filters & edfDirty) == edfDirty) && entity.Dirty;
             draw &= (((filters & edfSelected ) == edfSelected ) && entity.Selected) || (((filters & edfSelected ) == 0) && !entity.Selected);
             draw &= (((filters & edfFirstTile) == edfFirstTile) && (entity.Image->ImageType == itTile && entity.Image->IsFirstOfType())) || (((filters & edfFirstTile) == 0) && !(entity.Image->ImageType == itTile && entity.Image->IsFirstOfType()));
        if (draw)
        {
            auto pt = TPoint(m_BorderScaled.x, m_BorderScaled.y);
            m_ImageMap[entity.Id]->Draw(entity.Pt + pt, m_Content.get(), entity.Selected);
            entity.Clean();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawMap()
{
    if (!m_ForceMapDraw)
    {
        // draw all dirty tile 0's (unselected)
        DrawEntities(edfDirty + edfFirstTile);
        // draw all other dirty non tile 0's  (unselected)
        DrawEntities(edfDirty);
        // draw all dirty tile 0's (selected)
        DrawEntities(edfDirty + edfSelected + edfFirstTile);
        // draw all other dirty non tile 0's  (selected)
        DrawEntities(edfDirty + edfSelected);
    }
    else
    {
        // draw the tile 0's (unselected)
        DrawEntities(edfForce + edfFirstTile);
        // draw all non tile 0's (unselected)
        DrawEntities(edfForce);
        // draw the selected tile 0's (selected)
        DrawEntities(edfForce + edfSelected + edfFirstTile);
        // draw all the selected non tile 0's (selected)
        DrawEntities(edfForce + edfSelected);
    }
    m_ForceMapDraw = false;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawSelectedRoom() const
{
    if (m_ShowSelectedRoom)
    {
        auto shade = std::make_unique<TBitmap>();
        shade->PixelFormat = pf32bit;
        shade->Width = 1;
        shade->Height = 1;
        ((TColor*)shade->ScanLine[0])[0] = (TColor)0x7F00FF00;
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        auto ww = m_TileSize.cx * m_WindowSize.cx;
        auto wh = m_TileSize.cy * m_WindowSize.cy;
        auto pt = MapToView(TPoint(m_SelectedRoom.cx * ww, m_SelectedRoom.cy * wh));
        AlphaBlend(m_View->Picture->Bitmap->Canvas->Handle, pt.x, pt.y, ww * m_Scale.x + 1, wh * m_Scale.y + 1, shade->Canvas->Handle, 0, 0, 1, 1, bfn);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawStartRoom() const
{
    if (m_ShowStartRoom)
    {
        auto shade = std::make_unique<TBitmap>();
        shade->PixelFormat = pf32bit;
        shade->Width = 1;
        shade->Height = 1;
        ((TColor*)shade->ScanLine[0])[0] = (TColor)0x7FFFFF00;
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        auto ww = m_TileSize.cx * m_WindowSize.cx;
        auto wh = m_TileSize.cy * m_WindowSize.cy;
        auto pt = MapToView(TPoint(m_StartRoom.x * ww, m_StartRoom.y * wh));
        AlphaBlend(m_View->Picture->Bitmap->Canvas->Handle, pt.x, pt.y, ww * m_Scale.x + 1, wh * m_Scale.y + 1, shade->Canvas->Handle, 0, 0, 1, 1, bfn);
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

    if (m_ForceMapDraw)
    {
        Clear();
    }

    // draw the entities
    DrawMap();
    // show the map
    auto vw = ((int)(m_View->Width  / m_Scale.x)) * m_Scale.x;
    auto vh = ((int)(m_View->Height / m_Scale.y)) * m_Scale.x;
    auto cx = m_PositionMS.X;
    auto cy = m_PositionMS.Y;
    auto cw = (int)(vw / m_Scale.x);
    auto ch = (int)(vh / m_Scale.y);
    StretchBlt(m_View->Picture->Bitmap->Canvas->Handle, 0, 0, vw, vh, m_Content->Canvas->Handle, cx, cy, cw, ch, SRCCOPY);
    DrawGrids();
    DrawGroupSelect();
    DrawSelectedRoom();
    DrawStartRoom();
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
    m_Entities.clear();
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
EntityList __fastcall TileEditor::GetSelection() const
{
    EntityList selection;
    std::copy_if(m_Entities.begin(), m_Entities.end(), back_inserter(selection), [](const Entity& e){ return e.Selected; });
#if 0   // Re-Position to Zero
    // reposition the entities to 0,0
    // find the minimum position
    int minX = 1410065408;
    int minY = 1410065408;
    for (auto& e : selection)
    {
        minX = Min(minX, e.Pt.x);
        minY = Min(minY, e.Pt.y);
    }
    // re-adjust all entities
    for (auto& e : selection)
    {
        e.Pt = TPoint(e.Pt.x - minX, e.Pt.y - minY);
    }
#else   // Add +1, +1 tile size to each entity
    for (auto& e : selection)
    {
        e.Pt += TPoint(m_TileSize.cx, m_TileSize.cy);
    }
#endif
    return selection;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DeleteSelection()
{
    for (auto it = m_Entities.begin(); it != m_Entities.end();)
    {
        if ((*it).Selected)
        {
            it = m_Entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
    m_SelectionCount = 0;
    RefreshImages();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Add(const EntityList& entities)
{
    m_SelectionCount = entities.size();
    m_PrevMouseMode = mmGroupSelect;
    m_MouseMode = mmTool;
    m_Entities.insert(m_Entities.end(), entities.begin(), entities.end());
    RefreshImages();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UnselectAll()
{
    m_SelectionCount = 0;
    for (auto& e : m_Entities) e.Selected = false;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SelectRoom(TSize room)
{
    m_SelectedRoom = room;
    UnselectAll();
//    const auto& wi = theDocumentManager.ProjectConfig()->Window;
//    auto minx = room.cx * m_TileSize.cx * wi.Width;
//    auto miny = room.cy * m_TileSize.cy * wi.Height;
//    auto maxx = minx + (m_TileSize.cx * wi.Width);
//    auto maxy = miny + (m_TileSize.cy * wi.Height);
//
//    for (auto& e : m_Entities)
//    {
//        auto pt = e.Pt;
//        if (minx <=  pt.x && pt.x < maxx && miny <= pt.y && pt.y < maxy)
//        {
//            e.Selected = true;
//        }
//    }
    Messaging::Bus::Publish<RoomSelected>(RoomSelected(room));
    UpdateMap();
}
//---------------------------------------------------------------------------
int __fastcall TileEditor::Snap(int value, int range)
{
    return (value / range) * m_TileSize.cx;
}
//---------------------------------------------------------------------------

