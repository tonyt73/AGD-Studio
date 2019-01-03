//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.Math.hpp>
#include "TileEditor.h"
#include "Project/DocumentManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TileEditor::TileEditor(TImage* const view, Agdx::ImageMap& imageMap, const TSize& rooms, bool usesGridTile, bool usesGridRoom, int border, bool readOnly)
: m_View(view)
, m_ImageMap(imageMap)
, m_Rooms(rooms)
, m_UsesGridTile(usesGridTile)
, m_UsesGridRoom(usesGridRoom)
, m_ShowGridTile(false)
, m_ShowGridRoom(usesGridRoom)
, m_ShowSelectedRoom(false)
, m_ShowStartRoom(false)
, m_Border(border)
, m_ScaleFactor(2)
, m_MouseMode(mmTool)
, m_MousePanning(false)
, m_SelectionMove(false)
, m_ForceMapDraw(false)
, m_SelectionCount(0)
, m_SelectedEntity(-1)
, m_Tile0Id(-1)
, m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_ReadOnly(readOnly)
{
    Scale = m_ScaleFactor;

    CreateViewBitmap();
    Clear();
}
//---------------------------------------------------------------------------
__fastcall TileEditor::~TileEditor()
{
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
void __fastcall TileEditor::Clear()
{
    PatBlt(m_Content->Canvas->Handle, m_BorderScaled.x, m_BorderScaled.y, m_Content->Width, m_Content->Height, BLACKNESS);
    if (m_Tile0Id != -1 && m_ImageMap[m_Tile0Id])
    {
        // clear the map using tile 0's
        const auto& wi = theDocumentManager.ProjectConfig()->Window;
        auto cw = wi.Width  * m_TileSize.cx;
        auto ch = wi.Height * m_TileSize.cy;
        auto tile0 = std::make_unique<Graphics::TBitmap>();
        tile0->PixelFormat = pf32bit;
        tile0->Width = m_ImageMap[m_Tile0Id]->Canvas().Width;
        tile0->Height = m_ImageMap[m_Tile0Id]->Canvas().Height;
        m_ImageMap[m_Tile0Id]->Canvas().Assign(tile0.get());
        for (auto y = m_BorderScaled.y; y < m_ContentSize.cy - (m_BorderScaled.y * 2); y += tile0->Height)
        {
            for (auto x = m_BorderScaled.x; x < m_ContentSize.cx - (m_BorderScaled.x * 2); x += tile0->Width)
            {
                BitBlt(m_Content->Canvas->Handle, x, y, tile0->Width, tile0->Height, tile0->Canvas->Handle, 0, 0, SRCCOPY);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ValidatePosition()
{
    m_MapOffsetMS.X = max(0, (int)min(m_ContentSize.cx - (int)(m_View->Width  / m_Scale.x), m_MapOffsetMS.X));
    m_MapOffsetMS.Y = max(0, (int)min(m_ContentSize.cy - (int)(m_View->Height / m_Scale.y), m_MapOffsetMS.Y));
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::MapToView(const TPoint& pt) const
{
    auto x = m_Border + ((pt.x - m_MapOffsetMS.X) * m_Scale.x);
    auto y = m_Border + ((pt.y - m_MapOffsetMS.Y) * m_Scale.y);
    return TPoint(x, y);
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::ViewToMap(int X, int Y) const
{
    auto pt = TPoint(X / m_Scale.x, Y / m_Scale.y);
    auto bt = TPoint(m_BorderScaled.x, m_BorderScaled.y);
    return (m_MapOffsetMS + (pt - bt));
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownSelectMode(TMouseButton Button, TShiftState Shift, int X, int Y)
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
            ::Messaging::Bus::Publish<StartRoomSet>(StartRoomSet(m_StartRoom));
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
    if (m_MouseMode == mmTool && m_Mode == temSelect && Shift.Contains(ssCtrl) && Button == mbLeft)
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
        ::Messaging::Bus::Publish<StartRoomSet>(StartRoomSet(m_StartRoom));
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownPencilMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_SelectedEntity != - 1 && Shift.Contains(ssLeft))
    {
        m_MapPencilTool.Width  = m_ContentSize.cx - (m_BorderScaled.x * 2);
        m_MapPencilTool.Height = m_ContentSize.cy - (m_BorderScaled.y * 2);
        m_MapPencilTool.Begin(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y), Shift);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownLineMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownShapeMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_SelectedEntity != - 1 && Shift.Contains(ssLeft))
    {
        m_MapRectTool.Width  = m_ContentSize.cx - (m_BorderScaled.x * 2);
        m_MapRectTool.Height = m_ContentSize.cy - (m_BorderScaled.y * 2);
        m_MapRectTool.Begin(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y), Shift);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssShift) && Button == mbLeft)
    {
        m_MousePanning = true;
        Screen->Cursor =  crSizeAll;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
    }
    else
    {
        switch (m_Mode)
        {
            case temSelect:
                OnMouseDownSelectMode(Button, Shift, X, Y);
                break;
            case temPencil:
                OnMouseDownPencilMode(Button, Shift, X, Y);
                break;
            case temLine:
                OnMouseDownLineMode(Button, Shift, X, Y);
                break;
            case temShape:
                OnMouseDownShapeMode(Button, Shift, X, Y);
                break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMoveSelectMode(TShiftState Shift, int X, int Y)
{
    auto dPt = TPoint((X - m_LastMouse.X) / m_Scale.x, (Y - m_LastMouse.Y) / m_Scale.y);
    if (m_SelectionMove)
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
void __fastcall TileEditor::OnMouseMovePencilMode(TShiftState Shift, int X, int Y)
{
    if (!ReadOnly && m_SelectedEntity != - 1 && !Shift.Contains(ssLeft))
    {
        m_ToolEntities.clear();
        m_SingleSelect.Pt = ViewToMap(X, Y);
        auto x = Snap(std::max(0L, std::min(m_SingleSelect.Pt.x, m_ContentSize.cx - (int)(m_BorderScaled.x * 2) - m_TileSize.cx)), m_TileSize.cx);
        auto y = Snap(std::max(0L, std::min(m_SingleSelect.Pt.y, m_ContentSize.cy - (int)(m_BorderScaled.y * 2) - m_TileSize.cy)), m_TileSize.cy);
        m_SingleSelect.Pt = TPoint(x, y);
        m_ToolEntities.push_back(m_SingleSelect);
        UpdateMap();
    }
    else if (m_SelectedEntity != - 1 && Shift.Contains(ssLeft))
    {
        m_MapPencilTool.Move(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y), Shift);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMoveLineMode(TShiftState Shift, int X, int Y)
{
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMoveShapeMode(TShiftState Shift, int X, int Y)
{
    if (!ReadOnly && m_SelectedEntity != - 1 && !Shift.Contains(ssLeft))
    {
        m_ToolEntities.clear();
        m_SingleSelect.Pt = ViewToMap(X, Y);
        auto x = Snap(std::max(0L, std::min(m_SingleSelect.Pt.x, m_ContentSize.cx - (int)(m_BorderScaled.x * 2) - m_TileSize.cx)), m_TileSize.cx);
        auto y = Snap(std::max(0L, std::min(m_SingleSelect.Pt.y, m_ContentSize.cy - (int)(m_BorderScaled.y * 2) - m_TileSize.cy)), m_TileSize.cy);
        m_SingleSelect.Pt = TPoint(x, y);
        m_ToolEntities.push_back(m_SingleSelect);
        UpdateMap();
    }
    else if (m_SelectedEntity != - 1 && Shift.Contains(ssLeft))
    {
        m_MapRectTool.Move(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y), Shift);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMove(TShiftState Shift, int X, int Y)
{
    auto dPt = TPoint((X - m_LastMouse.X) / m_Scale.x, (Y - m_LastMouse.Y) / m_Scale.y);
    if (m_MousePanning)
    {
        m_MapOffsetMS -= dPt;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
        Refresh();
    }
    else
    {
        switch (m_Mode)
        {
            case temSelect:
                OnMouseMoveSelectMode(Shift, X, Y);
                break;
            case temPencil:
                OnMouseMovePencilMode(Shift, X, Y);
                break;
            case temLine:
                OnMouseMoveLineMode(Shift, X, Y);
                break;
            case temShape:
                OnMouseMoveShapeMode(Shift, X, Y);
                break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpSelectMode(TMouseButton Button, TShiftState Shift, int X, int Y)
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
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpPencilMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_SelectedEntity != - 1)
    {
        m_MapPencilTool.End(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y));
        ReplaceEntities();
    }
    m_ToolEntities.clear();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpLineMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_SelectedEntity != - 1)
    {
        m_MapPencilTool.End(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y));
        ReplaceEntities();
    }
    m_ToolEntities.clear();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpShapeMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_SelectedEntity != - 1)
    {
        m_MapRectTool.End(m_ToolEntities, m_SingleSelect, ViewToMap(X, Y));
        ReplaceEntities();
    }
    m_ToolEntities.clear();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_MousePanning)
    {
        m_MousePanning = false;
    }
    else
    {
        switch (m_Mode)
        {
            case temSelect:
                OnMouseUpSelectMode(Button, Shift, X, Y);
                break;
            case temPencil:
                OnMouseUpPencilMode(Button, Shift, X, Y);
                break;
            case temLine:
                OnMouseUpLineMode(Button, Shift, X, Y);
                break;
            case temShape:
                OnMouseUpShapeMode(Button, Shift, X, Y);
                break;
        }
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
    m_Tile0Id = id;
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetSelectedEntity(unsigned int id)
{
    m_SelectedEntity = -1;
    auto document = dynamic_cast<ImageDocument*>(theDocumentManager.Get(id));
    if (document != nullptr)
    {
        if (m_Mode != temSelect)
        {
            for (auto& e : m_ToolEntities)
            {
                e.Id = document->Id;
                e.Dirty = true;
            }
            UpdateMap();
        }
        m_SingleSelect.Id = document->Id;
        m_SingleSelect.Dirty = true;
        m_SingleSelect.Selected = false;
        m_SelectedEntity = id;
    }
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
void __fastcall TileEditor::SetMode(TEMode mode)
{
    m_Mode = mode;
    m_ToolEntities.clear();
    UpdateMap();
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

    auto xs =  m_Border - (m_MapOffsetMS.X * m_Scale.x);
    auto xe = xs + ((m_ContentSize.cx - (m_BorderScaled.x * 2)) * m_Scale.x);
    auto ys =  m_Border - (m_MapOffsetMS.Y * m_Scale.y);
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
//------    ---------------------------------------------------------------------
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
void __fastcall TileEditor::DrawToolEntities()
{
    if (!ReadOnly)
    {
        for (auto& entity : m_ToolEntities)
        {
            auto pt = TPoint(m_BorderScaled.x, m_BorderScaled.y);
            auto x = Snap(std::max(0L, std::min(pt.x, m_ContentSize.cx - (int)(m_BorderScaled.x * 2) - m_TileSize.cx)), m_TileSize.cx);
            auto y = Snap(std::max(0L, std::min(pt.y, m_ContentSize.cy - (int)(m_BorderScaled.y * 2) - m_TileSize.cy)), m_TileSize.cy);
            m_SingleSelect.Pt = TPoint(x, y);
            m_ImageMap[entity.Id]->Draw(entity.Pt + pt, m_Content.get(), false);
            entity.Clean();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawMap()
{
    auto filter = m_ForceMapDraw ? edfForce : edfDirty;
    // draw all dirty tile 0's (unselected)
    DrawEntities(filter + edfFirstTile);
    // draw all other dirty non tile 0's  (unselected)
    DrawEntities(filter);
    // draw all dirty tile 0's (selected)
    DrawEntities(filter + edfSelected + edfFirstTile);
    // draw all other dirty non tile 0's  (selected)
    DrawEntities(filter + edfSelected);
    DrawToolEntities();
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
    auto cx = m_MapOffsetMS.X;
    auto cy = m_MapOffsetMS.Y;
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
void __fastcall TileEditor::SetEntities(const EntityList& entities)
{
    m_Entities.clear();
    m_Entities = entities;
    for (auto& e : m_Entities) e.Dirty = true;
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
EntityList __fastcall TileEditor::GetSelection(bool resetToOrigin) const
{
    EntityList selection;
    std::copy_if(m_Entities.begin(), m_Entities.end(), back_inserter(selection), [](const Entity& e){ return e.Selected; });
    if (!resetToOrigin)
    {
        // move the selected entity down 1 and across 1
        for (auto& e : selection)
        {
            e.Pt += TPoint(m_TileSize.cx, m_TileSize.cy);
        }
    }
    else
    {
        // reposition the entities to 0,0 (origin)
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
    }
    return selection;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DeleteSelection()
{
    m_Entities.erase(std::remove_if(m_Entities.begin(),m_Entities.end(),
        [&](const Entity& entity) { return entity.Selected; }), m_Entities.end());
    m_SelectionCount = 0;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Add(const EntityList& entities)
{
    m_SelectionCount = entities.size();
    m_PrevMouseMode = mmGroupSelect;
    m_MouseMode = mmTool;
    m_Entities.insert(m_Entities.end(), entities.begin(), entities.end());
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UnselectAll()
{
    m_SelectionCount = 0;
    for (auto& e : m_Entities)
    {
        e.Selected = false;
        e.Dirty = true;
    }
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SelectRoom(TSize room)
{
    m_SelectedRoom = room;
    UnselectAll();
    ::Messaging::Bus::Publish<RoomSelected>(RoomSelected(room));
    UpdateMap();
}
//---------------------------------------------------------------------------
int __fastcall TileEditor::Snap(int value, int range)
{
    return ((int)(value / range)) * range;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ReplaceEntities()
{
    for (auto& e : m_ToolEntities)
    {
        // remove the existing entity at the location
        m_Entities.erase(std::remove_if(m_Entities.begin(),m_Entities.end(),
            [&](const Entity& entity) { return entity.Pt.x == e.Pt.x && entity.Pt.y == e.Pt.y; }), m_Entities.end());
        // add the new entity at the location
        m_Entities.push_back(e);
    }
}
//---------------------------------------------------------------------------

