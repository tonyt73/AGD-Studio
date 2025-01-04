//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "TileEditor.h"
#include "Visuals/BlockTypes.h"
#include "../MouseState.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Object.h"
#include "Project/Documents/Window.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const TColor c_ColorRoomSelected    = static_cast<TColor>(0x7F00FF00);   // 127 alpha - green
const TColor c_ColorStartRoom       = static_cast<TColor>(0x7FFFFF00);   // 127 alpha - yellow
const TColor c_ColorDisabledRoom    = static_cast<TColor>(0x7FFF00FF);   // 127 alpha - purple
const TColor c_ColorTileGrid        = static_cast<TColor>(0x00004080);   // a kind of light brown/yellow
const TColor c_ColorRoomGrid        = static_cast<TColor>(0x0048BAF7);   // a kind of dark brown/yellow
const TColor c_ColorEntitySelected  = static_cast<TColor>(0x7F00FF00);   // 127 alpha - green
const TColor c_ColorHoverEntity     = static_cast<TColor>(0x7F00AF00);   // 127 alpha - darker green
//---------------------------------------------------------------------------
__fastcall TileEditor::TileEditor(TImage* const view, Visuals::ImageMap& imageMap, const TSize& rooms, bool usesGridTile, bool usesGridRoom, int border, bool readOnly)
: m_View(view)
, m_LockIcon(nullptr)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_ImageMap(imageMap)
, m_ScaleFactor(2)
, m_Scale(1.f, 1.f)
, m_ForceMapDraw(false)
, m_MousePanning(false)
, m_ShowGridTile(false)
, m_ShowGridRoom(usesGridRoom)
, m_SelectionMove(false)
, m_UsesGridTile(usesGridTile)
, m_UsesGridRoom(usesGridRoom)
, m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum)
, m_Rooms(rooms)
, m_MouseMode(mmTool)
, m_Border(border)
, m_SelectionCount(0)
, m_Tile0Id(0)
, m_ReadOnly(readOnly)
, m_ShowSelectedRoom(false)
, m_ShowSpecialRooms(false)
, m_ShowRoomNumbers(false)
, m_ShowTileTypes(false)
, m_ShowSpriteTypes(false)
, m_ActiveMapTool(nullptr)
, FOnEntitySelected(nullptr)
, FRetrieveRoomIndex(nullptr)
{
    assert(view != nullptr);
    Scale = m_ScaleFactor;

    m_Registrar.Subscribe<WindowChangedEvent>(_FnBind(TileEditor::OnWindowChanged));
    m_Registrar.Subscribe<SpecialRoomChanged>(_FnBind(TileEditor::OnSpecialRoomChanged));

    m_View->Picture->Bitmap->Canvas->Font->Style = TFontStyles() << fsBold;
    CreateViewBitmap();
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnWindowChanged(const WindowChangedEvent& event)
{
    if (m_Window.Width() != event.Window.Width() || m_Window.Height() != event.Window.Height()) {
        CreateViewBitmap();
        Clear();
        Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnSpecialRoomChanged(const SpecialRoomChanged& event)
{
    if (event.Index < Project::g_MaxRooms) {
        m_StartRoom = event.Room;
    } else {
        m_DisabledRoom = event.Room;
        // update the objects in the disabled room
        auto roomSize = TSize(m_Window.Width() * m_TileSize.cx, m_Window.Height() * m_TileSize.cy);
        for (auto& entity : m_Entities) {
            if (entity.RoomIndex == Project::g_RoomIndexDisabled) {
                auto roomPt = TPoint(static_cast<int>(entity.Pt.X / roomSize.cx), static_cast<int>(entity.Pt.Y / roomSize.cy));
                // move the entity to the new location
                roomPt.X *= roomSize.cx;
                roomPt.Y *= roomSize.cy;
                entity.Pt -= roomPt;
                entity.Pt += TPoint(DisabledRoom.X * roomSize.cx, DisabledRoom.Y * roomSize.cy);
                entity.Dirty = true;
            }
        }

    }
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::CreateViewBitmap()
{
    const auto& wi = dynamic_cast<Project::WindowDocument*>(theDocumentManager.Get("Window", "Definition", "Window"));
    assert(wi != nullptr);
    m_Window = wi->Rect;
    m_Content = std::make_unique<TBitmap>();
    m_Content->PixelFormat = pf32bit;
    m_ContentSize.cx = m_TileSize.cx * m_Window.Width()  * m_Rooms.cx;
    m_ContentSize.cy = m_TileSize.cy * m_Window.Height() * m_Rooms.cy;
    m_Content->Width  = m_ContentSize.cx + (m_BorderScaled.x * 2);
    m_Content->Height = m_ContentSize.cy + (m_BorderScaled.y * 2);
    PatBlt(m_Content->Canvas->Handle, 0, 0, m_Content->Width, m_Content->Height, BLACKNESS);

    m_Tile0Content = std::make_unique<TBitmap>();
    m_Tile0Content->PixelFormat = pf32bit;
    m_Tile0Content->Width  = m_ContentSize.cx;
    m_Tile0Content->Height = m_ContentSize.cy;
    UpdateTile0Content();
    m_ForceMapDraw = true;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UpdateTile0Content()
{
    PatBlt(m_Tile0Content->Canvas->Handle, 0, 0, m_Tile0Content->Width, m_Tile0Content->Height, BLACKNESS);
    if (m_Tile0Id && m_ImageMap[m_Tile0Id]) {
        auto tile0 = std::make_unique<TBitmap>();
        tile0->PixelFormat = pf32bit;
        tile0->Width = m_ImageMap[m_Tile0Id]->Canvas().Width;
        tile0->Height = m_ImageMap[m_Tile0Id]->Canvas().Height;
        m_ImageMap[m_Tile0Id]->Canvas().Assign(tile0.get());
        for (auto y = 0; y < m_Tile0Content->Height; y += tile0->Height) {
            for (auto x = 0; x < m_Tile0Content->Width; x += tile0->Width) {
                BitBlt(m_Tile0Content->Canvas->Handle, x, y, tile0->Width, tile0->Height, tile0->Canvas->Handle, 0, 0, SRCCOPY);
            }
        }
        Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Clear()
{
    PatBlt(m_Content->Canvas->Handle, 0, 0, m_Content->Width, m_Content->Height, BLACKNESS);
    if (m_Tile0Id && m_ImageMap[m_Tile0Id]) {
        // clear the map using tile 0's
        BitBlt(m_Content->Canvas->Handle, m_BorderScaled.x, m_BorderScaled.y, m_Content->Width - (m_BorderScaled.x * 2), m_Content->Height - (m_BorderScaled.y * 2), m_Tile0Content->Canvas->Handle, 0, 0, SRCCOPY);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ValidatePosition()
{
    auto window = TSize(static_cast<int>(static_cast<float>(m_View->Width) / m_Scale.x), static_cast<int>(static_cast<float>(m_View->Height) / m_Scale.y));
    m_MapOffsetMS.X = std::max(0, std::min(static_cast<int>((m_BorderScaled.x * 2) + m_ContentSize.cx - window.cx), static_cast<int>(m_MapOffsetMS.X)));
    m_MapOffsetMS.Y = std::max(0, std::min(static_cast<int>((m_BorderScaled.y * 2) + m_ContentSize.cy - window.cy), static_cast<int>(m_MapOffsetMS.Y)));
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::MapToView(const TPoint& pt) const
{
    auto x = m_Border + static_cast<int>(static_cast<float>(pt.x - m_MapOffsetMS.X) * m_Scale.x);
    auto y = m_Border + static_cast<int>(static_cast<float>(pt.y - m_MapOffsetMS.Y) * m_Scale.y);
    return TPoint(x, y);
}
//---------------------------------------------------------------------------
TPoint __fastcall TileEditor::ViewToMap(int X, int Y) const
{
    auto pt = TPoint(static_cast<int>(static_cast<float>(X) / m_Scale.x), static_cast<int>(static_cast<float>(Y) / m_Scale.y));
    auto bt = TPoint(m_BorderScaled.x, m_BorderScaled.y);
    return (m_MapOffsetMS + (pt - bt));
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownSelectMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MouseState ms(Button, Shift);
    if (ms.Left) {
        if (ms.NoModifiers) {
            if (m_ReadOnly) {
                // Change current room selection
                // work out the room number
                auto pt = ViewToMap(X, Y);
                pt.x /= m_TileSize.cx * m_Window.Width();
                pt.y /= m_TileSize.cy * m_Window.Height();
                // change the current edited room
                SelectRoom(TPoint(pt.x, pt.y));
            } else if (m_SelectionCount > 0 || m_HoverEntity.Id) {
                Project::MapEntity entity;
                if (!GetEntityUnderMouse(X, Y, entity, Visuals::itSprite) && !GetEntityUnderMouse(X, Y, entity, Visuals::itObject) && !GetEntityUnderMouse(X, Y, entity, Visuals::itTile)) {
                    // clear selection with a click on empty space
                    UnselectAll();
                    m_MouseMode = mmTool;
                } else if (m_SelectionCount <= 1 && m_HoverEntity.Id && FOnEntitySelected != nullptr) {
                    // selecting a single item; ready to move the selection
                    // if a single entity is selected then inform the UI
                    m_ToolEntity = m_HoverEntity;
                    FOnEntitySelected(m_ToolEntity);
                    SelectHover();
                }
                m_SelectionMove = m_SelectionCount > 0;
                m_LastMouse.X = X;
                m_LastMouse.Y = Y;
            }
        } else if (m_MouseMode == mmTool && m_Mode == temSelect && ms.Ctrl) {
            // start group selecting the entities
            m_MouseMode = mmGroupSelect;
            m_GroupSelectSrtMS = ViewToMap(X, Y);
            m_GroupSelectEndMS = m_GroupSelectSrtMS;
            m_GroupSelectSrtMS.X = Snap(m_GroupSelectSrtMS.X, m_TileSize.cx);
            m_GroupSelectSrtMS.Y = Snap(m_GroupSelectSrtMS.Y, m_TileSize.cy);
            m_GroupSelectEndMS.X = Snap(m_GroupSelectEndMS.X, m_TileSize.cx);
            m_GroupSelectEndMS.Y = Snap(m_GroupSelectEndMS.Y, m_TileSize.cy);
        } else if (ShowSpecialRooms && ms.Alt) {
            // try to change the selected room on the map
            auto pt = ViewToMap(X, Y);
            pt.x /= m_TileSize.cx * m_Window.Width();
            pt.y /= m_TileSize.cy * m_Window.Height();
            Bus::Publish<SetSpecialRoom>(SetSpecialRoom(pt, 0));
        } else if (ShowSpecialRooms && ms.AltShift) {
            auto pt = ViewToMap(X, Y);
            pt.x /= m_TileSize.cx * m_Window.Width();
            pt.y /= m_TileSize.cy * m_Window.Height();
            // change the current edited room
            Bus::Publish<SetSpecialRoom>(SetSpecialRoom(pt, Project::g_RoomIndexDisabled));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDownMapToolMode(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MouseState ms(Button, Shift);
    if (ToolEntity && ms.Left && m_ActiveMapTool) {
        m_ActiveMapTool->Width  = m_ContentSize.cx;
        m_ActiveMapTool->Height = m_ContentSize.cy;
        m_ActiveMapTool->Begin(m_ToolEntities, m_ToolEntity, ViewToMap(X, Y), Shift);
        AssignRoomIndexes(m_ToolEntities);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MouseState ms(Button, Shift);
    if (ms.Left && ms.Shift) {
        m_MousePanning = true;
        Screen->Cursor =  crSizeAll;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
    } else {
        switch (m_Mode) {
        case temSelect:
            OnMouseDownSelectMode(Button, Shift, X, Y);
            break;
        case temPencil:
        case temLine:
        case temRect:
            OnMouseDownMapToolMode(Button, Shift, X, Y);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMoveSelectMode(TShiftState Shift, int X, int Y)
{
    MouseState ms(Shift);
    auto dPt = TPoint(static_cast<int>(static_cast<float>(X - m_LastMouse.X) / m_Scale.x), static_cast<int>(static_cast<float>(Y - m_LastMouse.Y) / m_Scale.y));
    if (m_SelectionMove) {
        // we are moving the selected enitities
        // would any of the selected entities move out of bounds?
        auto outOfBounds = false;
        for (auto& e : m_Entities) {
            if (e.Selected) {
                auto pt = e.Pt - e.DragPt + dPt;
                if (pt.x < 0 || pt.y < 0 || (pt.x + m_TileSize.cx) >= m_ContentSize.cx || (pt.y + m_TileSize.cy) >= m_ContentSize.cy) {
                    // yes, then we leave them where they are and stop moving the selection
                    // TODO: Snap the selection to the bounds
                    outOfBounds = true;
                    break;
                }
            }
        }
        if (!outOfBounds) {
            // move the selected enitities
            for (auto& e : m_Entities) {
                if (e.Selected) {
                    e.DragPt = dPt;
                }
            }
            UpdateMap();
        }
    }
    else if (!m_ReadOnly) {
        // workspace/scratch pad mode
        switch (m_MouseMode) {
            case mmTool: {
                if (m_Mode == temSelect && !ms.Left && ms.NoModifiers) {
                    bool refresh = ClearHover();
                    // find an object that intersects the mouse
                    Project::MapEntity entity;
                    if ((GetEntityUnderMouse(X, Y, entity, Visuals::itSprite) || GetEntityUnderMouse(X, Y, entity, Visuals::itObject) || GetEntityUnderMouse(X, Y, entity, Visuals::itTile)) /*&& !entity.Selected*/) {
                        m_HoverEntity = entity;
                        refresh = true;
                    }
                    if (ms.Middle) {
                        DeleteSelection();
                        refresh = true;
                    }
                    if (refresh) {
                        Refresh();
                    }
                }
                break;
            }
            case mmGroupSelect: {
                // dragging the selection rect
                m_GroupSelectEndMS = ViewToMap(X, Y);
                m_GroupSelectEndMS.X = Snap(m_GroupSelectEndMS.X, m_TileSize.cx) + m_TileSize.cx;
                m_GroupSelectEndMS.Y = Snap(m_GroupSelectEndMS.Y, m_TileSize.cy) + m_TileSize.cy;
                auto minX = std::min(m_GroupSelectSrtMS.X, m_GroupSelectEndMS.X);
                auto maxX = std::max(m_GroupSelectSrtMS.X, m_GroupSelectEndMS.X);
                auto minY = std::min(m_GroupSelectSrtMS.Y, m_GroupSelectEndMS.Y);
                auto maxY = std::max(m_GroupSelectSrtMS.Y, m_GroupSelectEndMS.Y);
                if (minX != maxX && minY != maxY) {
                    UnselectAll(false);
                    for (auto& e : m_Entities) {
                        auto ex = e.Pt.x;
                        auto ey = e.Pt.y;
                        if (!e.Selected && (minX <= ex && ex + e.Image->Width <= maxX && minY <= ey && ey + e.Image->Height <= maxY)) {
                            e.Selected = true;
                            m_SelectionCount += 1;
                        }
                    }
                    Refresh();
                }
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMoveMapToolMode(TShiftState Shift, int X, int Y)
{
    MouseState ms(Shift);
    if (!ReadOnly && ToolEntity && !ms.Left) {
        // draw a single entity as a cursor
        m_ToolEntities.clear();
        auto pt = ViewToMap(X, Y);
        pt.x = Snap(std::max(0L, std::min(pt.x, m_ContentSize.cx - m_TileSize.cx)), m_TileSize.cx);
        pt.y = Snap(std::max(0L, std::min(pt.y, m_ContentSize.cy - m_TileSize.cy)), m_TileSize.cy);
        m_ToolEntity.Pt = pt;
        m_ToolEntities.push_back(m_ToolEntity);
        UpdateMap();
    } else if (ToolEntity && ms.Left && m_ActiveMapTool) {
        // draw the tool entity
        m_ActiveMapTool->Move(m_ToolEntities, m_ToolEntity, ViewToMap(X, Y), Shift);
        UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseMove(TShiftState Shift, int X, int Y)
{
    MouseState ms(Shift);
    auto dPt = TPoint(static_cast<int>(static_cast<float>(X - m_LastMouse.X) / m_Scale.x), static_cast<int>(static_cast<float>(Y - m_LastMouse.Y) / m_Scale.y));
    if (m_MousePanning) {
        m_MapOffsetMS -= dPt;
        m_LastMouse.X = X;
        m_LastMouse.Y = Y;
        Refresh();
    } else {
        switch (m_Mode) {
        case temSelect:
            OnMouseMoveSelectMode(Shift, X, Y);
            break;
        case temPencil:
        case temLine:
        case temRect:
            OnMouseMoveMapToolMode(Shift, X, Y);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpSelectMode(TMouseButton Button, TShiftState Shift, int, int)
{
    MouseState ms(Button, Shift);
    if (!m_ReadOnly) {
        m_PrevMouseMode = m_MouseMode;
        m_MouseMode = mmTool;
        m_ForceMapDraw = true;
    }
    if (m_SelectionMove) {
        m_SelectionMove = false;
        m_SelectionCount = 0;
        AssignRoomIndexes(m_Entities);
        // snap the selected items to the grid
        for (auto& e : m_Entities) {
            if (e.Selected) {
                // TODO: Some machines with hardware sprites might not have a grid limitation
                //       Should add this to the machine config and only apply if needed
                e.Pt = TPoint(Snap(e.Pt.X, m_TileSize.cx), Snap(e.Pt.Y, m_TileSize.cy));
                e.DragPt = TPoint();
                if (e.RoomLocked && e.RoomIndex <= Project::g_RoomIndexDisabled) {
                    // get the rooms coords
                    TRect rmPt;
                    for (auto i = 0; i < Project::g_MaxMapRoomsDown * Project::g_MaxMapRoomsAcross; i++) {
                        auto x = i % Project::g_MaxMapRoomsAcross;
                        auto y = i / Project::g_MaxMapRoomsDown;
                        auto ri = FRetrieveRoomIndex(TPoint(x, y), false);
                        if (ri == e.RoomIndex) {
                            rmPt.Left = x;
                            rmPt.Top = y;
                            break;
                        }
                    }
                    // get the X pixels into the map, then remove the left edge of the game window
                    // this makes the left edge where the screen edge would be
                    rmPt.Left = (rmPt.Left * m_Window.Width() * m_TileSize.cx) - (m_Window.Left * m_TileSize.cx);
                    // do the same for the top
                    rmPt.Top = (rmPt.Top * m_Window.Height() * m_TileSize.cy) - (m_Window.Top * m_TileSize.cy);
                    // window is maximum 1 byte wide and high (256)
                    rmPt.Right = rmPt.Left + 255;
                    rmPt.Bottom = rmPt.Top + 255;
                    // now make sure the entity isn't outside the screen space
                    auto ex = std::max(e.Pt.X, rmPt.Left);
                    ex = std::min(ex, rmPt.Right);
                    auto ey = std::max(e.Pt.Y, rmPt.Top);
                    ey = std::min(ey, rmPt.Bottom);
                    e.Pt = TPoint(ex, ey);
                }
                m_SelectionCount++;
            }
        }
        m_ForceMapDraw = true;
    }
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUpMapToolMode(TMouseButton, TShiftState, int X, int Y)
{
    if (ToolEntity && m_ActiveMapTool) {
        m_ActiveMapTool->End(m_ToolEntities, m_ToolEntity, ViewToMap(X, Y));
        ReplaceEntities();
    }
    m_ToolEntities.clear();
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_MousePanning) {
        m_MousePanning = false;
    } else {
        switch (m_Mode) {
        case temSelect:
            OnMouseUpSelectMode(Button, Shift, X, Y);
            break;
        case temPencil:
        case temLine:
        case temRect:
            OnMouseUpMapToolMode(Button, Shift, X, Y);
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
    UpdateTile0Content();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetToolEntity(unsigned int id)
{
    m_ToolEntity.Id = 0;
    auto document = dynamic_cast<Project::ImageDocument*>(theDocumentManager.Get(id));
    if (document != nullptr) {
        if (m_Mode != temSelect) {
            for (auto& e : m_ToolEntities) {
                e.Id = document->Id;
                e.Dirty = true;
            }
            UpdateMap();
        }
        m_ToolEntity.Id = document->Id;
        m_ToolEntity.Selected = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetScale(float scale)
{
    const auto& gm = m_GraphicsMode;
    m_ScaleFactor = scale;
    m_Scale.x = scale * gm.ScalarX;
    m_Scale.y = scale * gm.ScalarY;
    m_BorderScaled.x = static_cast<int>(static_cast<float>(m_Border) / m_Scale.x);
    m_BorderScaled.y = static_cast<int>(static_cast<float>(m_Border) / m_Scale.y);
    CreateViewBitmap();
    m_View->Picture->Bitmap->Canvas->Font->Size = (-12 * 72 * static_cast<int>(std::max(1.f, m_Scale.y))) / m_View->Picture->Bitmap->Canvas->Font->PixelsPerInch;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetMode(TEMode mode)
{
    m_Mode = mode;
    m_ToolEntities.clear();
    m_ActiveMapTool = nullptr;
    if (m_Mode == temPencil) {
        m_ActiveMapTool = &m_MapPencilTool;
    } else if (m_Mode == temLine) {
        m_ActiveMapTool = &m_MapLineTool;
    } else if (m_Mode == temRect) {
        m_ActiveMapTool = &m_MapRectTool;
    }
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetReadOnly(bool state)
{
    m_ReadOnly = state;
    if (m_ReadOnly) {
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
void __fastcall TileEditor::SetShowRoomNumbers(bool state)
{
    m_ShowRoomNumbers = state && m_UsesGridRoom;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetShowTileTypes(bool state)
{
    m_ShowTileTypes = state;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetShowSpriteTypes(bool state)
{
    m_ShowSpriteTypes = state;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetShowSpecialRooms(bool state)
{
    m_ShowSpecialRooms = state;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetStartRoomCoords(TPoint location)
{
    if ((location.x != m_StartRoom.x || location.y != m_StartRoom.y) && 0 <= location.x && location.y < m_Rooms.cx && 0 <= location.y && location.y < m_Rooms.cy) {
        m_StartRoom = location;
    }
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetDisabledRoomCoords(TPoint location)
{
    if ((location.x != m_StartRoom.x || location.y != m_StartRoom.y) && 0 <= location.x && location.y < Project::g_MaxMapRoomsAcross && 0 <= location.y && location.y < Project::g_MaxMapRoomsDown) {
        m_DisabledRoom = location;
    }
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetLockIcon(TImage* icon)
{
    m_LockIcon = icon;
    for (auto& e : m_Entities) {
        if (e.RoomLocked) {
            e.Dirty = true;
        }
    }
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetEntities(const Project::MapEntityList& entities)
{
    m_Entities.clear();
    m_Entities = entities;
    for (auto& e : m_Entities) {
        e.Selected = false;
        e.Dirty = true;
    }
}
//---------------------------------------------------------------------------
Project::MapEntityList __fastcall TileEditor::GetSelection(Visuals::ImageTypes type, bool resetToOrigin) const
{
    Project::MapEntityList selection;
    std::copy_if(m_Entities.begin(), m_Entities.end(), back_inserter(selection), [type](const Project::MapEntity& e){ return e.Selected && (e.Type == type || type == Visuals::itAll); });
    if (!resetToOrigin) {
        // move the selected entity down 1 and across 1
        for (auto& e : selection) {
            e.Pt += TPoint(m_TileSize.cx, m_TileSize.cy);
        }
    } else {
        ResetToOrigin(selection, TPoint(0,0));
    }
    return selection;
}
//---------------------------------------------------------------------------
const Project::MapEntityList& __fastcall TileEditor::GetEntities() const
{
    return m_Entities;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Get(const TRect& rect, Project::MapEntityList& entities) const
{
    // get all entities that start within the rect
    std::copy_if(m_Entities.begin(), m_Entities.end(), entities.begin(), [rect](const Project::MapEntity e) { return rect.Contains(e.Pt); });
}
//---------------------------------------------------------------------------
unsigned int __fastcall TileEditor::GetToolEntity() const
{
    return m_ToolEntity.Id;
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
    auto Canvas = m_View->Picture->Bitmap->Canvas;
    Canvas->Pen->Style = psSolid;

    auto xs = static_cast<int>(static_cast<float>(m_BorderScaled.x - m_MapOffsetMS.X) * m_Scale.x);
    auto xe = xs + static_cast<int>(static_cast<float>(m_ContentSize.cx) * m_Scale.x);
    auto ys =  static_cast<int>(static_cast<float>(m_BorderScaled.y - m_MapOffsetMS.Y) * m_Scale.y);
    auto ye = ys + static_cast<int>(static_cast<float>(m_ContentSize.cy) * m_Scale.y);
    if (m_UsesGridTile && m_ShowGridTile) {
        auto sx = static_cast<int>(static_cast<float>(m_TileSize.cx) * m_Scale.x);
        Canvas->Pen->Color = c_ColorTileGrid;
        for (auto x = xs; x <= xe; x += sx) {
            Canvas->MoveTo(x, ys);
            Canvas->LineTo(x, ye);
        }
        auto sy = static_cast<int>(static_cast<float>(m_TileSize.cy) * m_Scale.y);
        for (auto y = ys; y <= ye; y += sy) {
            Canvas->MoveTo(xs, y);
            Canvas->LineTo(xe, y);
        }
    }
    if (m_UsesGridRoom && m_ShowGridRoom) {
        Canvas->Pen->Color = c_ColorRoomGrid;
        auto rx = static_cast<int>(static_cast<float>(m_Window.Width()  * m_TileSize.cx) * m_Scale.x);
        auto ry = static_cast<int>(static_cast<float>(m_Window.Height() * m_TileSize.cy) * m_Scale.y);
        for (auto x = xs; x <= xe; x += rx) {
            Canvas->MoveTo(x, ys);
            Canvas->LineTo(x, ye);
        }
        for (auto y = ys; y <= ye; y += ry) {
            Canvas->MoveTo(xs    , y);
            Canvas->LineTo(xe + 1, y);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawRoomNumbers() const
{
    if (m_ShowRoomNumbers && FRetrieveRoomIndex) {
        auto Canvas = m_View->Picture->Bitmap->Canvas;
        Canvas->Font->Size = 10;
        Canvas->Font->Color = ThemeManager::Foreground;
        Canvas->Pen->Style = psSolid;
        auto xs = static_cast<int>(static_cast<float>(m_BorderScaled.x  - m_MapOffsetMS.X) * m_Scale.x);
        auto ys = static_cast<int>(static_cast<float>(m_BorderScaled.y  - m_MapOffsetMS.Y) * m_Scale.y);
        auto rx = static_cast<int>(static_cast<float>(m_Window.Width()  * m_TileSize.cx  ) * m_Scale.x);
        auto ry = static_cast<int>(static_cast<float>(m_Window.Height() * m_TileSize.cy  ) * m_Scale.y);
        auto ty = ys;
        for (auto y = 0; y < Project::g_MaxMapRoomsDown; y++) {
            auto tx = xs;
            for (auto x = 0; x < Project::g_MaxMapRoomsAcross; x++) {
                auto ri = FRetrieveRoomIndex(TPoint(x, y), false);
                if (ri <= Project::g_RoomIndexDisabled) {
                    // draw number/named room
                    auto room = ri != Project::g_RoomIndexDisabled ? IntToStr(ri) : "DISABLED";
                    auto ts = Canvas->TextExtent(room);
                    Canvas->Pen->Color = ThemeManager::Background;
                    Canvas->Brush->Color = ThemeManager::Background;
                    Canvas->Rectangle(TRect(tx, ty, tx + ts.Width + 6, ty + ts.Height + 4));
                    Canvas->Brush->Color = ThemeManager::Highlight;
                    Canvas->TextOut(tx + 3, ty + 2, room);
                }
                tx += rx;
            }
            ty += ry;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawSpriteTypes() const
{
    if (m_ShowSpriteTypes && m_ScaleFactor >= 2.0f) {
        auto Canvas = m_View->Picture->Bitmap->Canvas;
        Canvas->Font->Size = 8;
        Canvas->Font->Color = ThemeManager::Foreground;
        Canvas->Pen->Style = psSolid;
        for (auto& entity : m_Entities) {
            if (entity.IsSprite) {
                auto pt = entity.Pt;
                pt.x = Snap(pt.x + entity.Image->Width, m_TileSize.cx);
                pt.y = Snap(pt.y, m_TileSize.cy);
                pt = MapToView(pt);
                auto number = IntToStr(entity.SpriteType);
                auto ts = Canvas->TextExtent(number);
                Canvas->Pen->Color = ThemeManager::Background;
                Canvas->Brush->Color = ThemeManager::Background;
                pt.x -= ts.Width + 6;
                Canvas->Rectangle(TRect(pt.x, pt.y, pt.x + ts.Width + 6, pt.y + ts.Height + 4));
                Canvas->Brush->Color = ThemeManager::Highlight;
                Canvas->TextOut(pt.x + 3, pt.y + 2, number);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawEntityLocks() const
{
    auto Canvas = m_View->Picture->Bitmap->Canvas;
    for (auto& entity : m_Entities) {
        if (entity.RoomLocked && m_LockIcon != nullptr) {
            auto pt = entity.Pt;
            pt.x = Snap(pt.x, m_TileSize.cx);
            pt.y = Snap(pt.y, m_TileSize.cy);
            pt = MapToView(pt);
            Canvas->Draw(pt.x, pt.y, m_LockIcon->Picture->Graphic);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawGroupSelect() const
{
    if (m_MouseMode == mmGroupSelect) {
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
void __fastcall TileEditor::DrawEntities(int filters, Visuals::ImageTypes type)
{
    for (auto& entity : m_Entities) {
        bool draw  = (filters & edfForce) == edfForce;
             draw |= ((filters & edfDirty) == edfDirty) && entity.Dirty;
             draw &= type == Visuals::itInvalid ? true : entity.Type == type;
             draw &= (((filters & edfSelected ) == edfSelected ) && entity.Selected) || (((filters & edfSelected ) == 0) && !entity.Selected);
             draw &= (((filters & edfFirstTile) == edfFirstTile) && (entity.Image->ImageType == Visuals::itTile && entity.Image->IsFirstOfType())) || (((filters & edfFirstTile) == 0) && !(entity.Image->ImageType == Visuals::itTile && entity.Image->IsFirstOfType()));
        if (draw) {
            auto pt = entity.Pt;
            pt.x = Snap(pt.x, m_TileSize.cx);
            pt.y = Snap(pt.y, m_TileSize.cy);
            pt += m_BorderScaled;
            auto bt = entity.Image->GetLayer("blocktype");
            auto tileType = StrToIntDef(bt, 0);
            auto overlayColor = (entity.Selected ? c_ColorEntitySelected : (m_ShowTileTypes && tileType != -1 ? g_BlockColors[tileType] : clBlack));
            m_ImageMap[entity.Id]->Draw(pt, m_Content.get(), overlayColor);
            entity.Clean();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawToolEntities()
{
    if (!ReadOnly) {
        for (auto& entity : m_ToolEntities) {
            m_ImageMap[entity.Id]->Draw(entity.Pt + m_BorderScaled, m_Content.get());
            entity.Clean();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawHoverEntity()
{
    if (m_HoverEntity.Id && !m_HoverEntity.Selected) {
        m_ImageMap[m_HoverEntity.Id]->Draw(m_HoverEntity.Pt + m_BorderScaled, m_Content.get(), c_ColorHoverEntity);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawMap()
{
    auto filter = m_ForceMapDraw ? edfForce : edfDirty;
    // draw all dirty tile 0's (unselected)
    DrawEntities(filter + edfFirstTile, Visuals::itTile);
    // draw all other dirty non tile 0's  (unselected)
    DrawEntities(filter, Visuals::itTile);
    DrawEntities(filter, Visuals::itObject);
    DrawEntities(filter, Visuals::itSprite);
    // draw all other dirty non tile 0's  (selected)
    DrawEntities(filter + edfSelected);
    DrawToolEntities();
    DrawHoverEntity();
    m_ForceMapDraw = false;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawSelectedRoom() const
{
    if (m_ShowSelectedRoom) {
        auto shade = std::make_unique<TBitmap>();
        shade->PixelFormat = pf32bit;
        shade->Width = 1;
        shade->Height = 1;
        static_cast<TColor*>(shade->ScanLine[0])[0] = c_ColorRoomSelected;
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        auto ww = m_TileSize.cx * m_Window.Width();
        auto wh = m_TileSize.cy * m_Window.Height();
        auto pt = MapToView(TPoint(m_SelectedRoom.x * ww, m_SelectedRoom.y * wh));
        AlphaBlend(m_View->Picture->Bitmap->Canvas->Handle, pt.x, pt.y, static_cast<int>(static_cast<float>(ww) * m_Scale.x) + 1, static_cast<int>(static_cast<float>(wh) * m_Scale.y) + 1, shade->Canvas->Handle, 0, 0, 1, 1, bfn);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DrawSpecialRooms() const
{
    if (m_ShowSpecialRooms) {
        // make a 1x1 pixel bitmap
        auto shade = std::make_unique<TBitmap>();
        shade->PixelFormat = pf32bit;
        shade->Width = 1;
        shade->Height = 1;
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        auto ww = m_TileSize.cx * m_Window.Width();
        auto wh = m_TileSize.cy * m_Window.Height();
        auto pt = MapToView(TPoint(m_StartRoom.x * ww, m_StartRoom.y * wh));
        // set the color (start room)
        static_cast<TColor*>(shade->ScanLine[0])[0] = c_ColorStartRoom;
        // draw the start room
        AlphaBlend(m_View->Picture->Bitmap->Canvas->Handle, pt.x, pt.y, static_cast<int>(static_cast<float>(ww) * m_Scale.x) + 1, static_cast<int>(static_cast<float>(wh) * m_Scale.y) + 1, shade->Canvas->Handle, 0, 0, 1, 1, bfn);

        // set the color (disabled room)
        static_cast<TColor*>(shade->ScanLine[0])[0] = c_ColorDisabledRoom;
        pt = MapToView(TPoint(m_DisabledRoom.X * ww, m_DisabledRoom.Y * wh));
        // draw the disabled/inventory room
        AlphaBlend(m_View->Picture->Bitmap->Canvas->Handle, pt.x, pt.y, static_cast<int>(static_cast<float>(ww) * m_Scale.x) + 1, static_cast<int>(static_cast<float>(wh) * m_Scale.y) + 1, shade->Canvas->Handle, 0, 0, 1, 1, bfn);
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Refresh()
{
    ValidatePosition();
    if (m_View->Width != m_View->Picture->Bitmap->Width || m_View->Height != m_View->Picture->Bitmap->Height) {
        m_View->Picture->Bitmap->Width  = m_View->Width;
        m_View->Picture->Bitmap->Height = m_View->Height;
    }

    if (m_ForceMapDraw) {
        Clear();
    }

    // draw the entities
    DrawMap();
    // show the map
    auto cx = m_MapOffsetMS.X;
    auto cy = m_MapOffsetMS.Y;
    auto cw = static_cast<int>(static_cast<float>(m_View->Width ) / m_Scale.x);
    auto ch = static_cast<int>(static_cast<float>(m_View->Height) / m_Scale.y);
    if (cw > m_Content->Width || cy > m_Content->Height) {
        PatBlt(m_View->Picture->Bitmap->Canvas->Handle, 0, 0, m_View->Width, m_View->Height, BLACKNESS);
    }
    StretchBlt(m_View->Picture->Bitmap->Canvas->Handle, 0, 0, m_View->Width, m_View->Height, m_Content->Canvas->Handle, cx, cy, cw, ch, SRCCOPY);
    DrawSpriteTypes();
    DrawEntityLocks();
    DrawGrids();
    DrawRoomNumbers();
    DrawGroupSelect();
    DrawSelectedRoom();
    DrawSpecialRooms();
    m_View->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ResetToOrigin(Project::MapEntityList& list, const TPoint& originPt) const
{
    // reposition the entities to 0,0 (origin)
    // find the minimum position
    int minX = 1410065408;
    int minY = 1410065408;
    for (auto& e : list) {
        minX = Min(minX, e.Pt.x);
        minY = Min(minY, e.Pt.y);
    }
    // re-adjust all entities
    for (auto& e : list) {
        e.Pt = TPoint(e.Pt.x - minX, e.Pt.y - minY) + originPt;
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::DeleteSelection()
{
    m_Entities.erase(std::remove_if(m_Entities.begin(),m_Entities.end(), [&](const Project::MapEntity& entity) { return m_HoverEntity == entity || entity.Selected; }), m_Entities.end());
    m_SelectionCount = 0;
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Add(const Project::MapEntityList& entities)
{
    m_SelectionCount = static_cast<unsigned int>(entities.size());
    m_PrevMouseMode = mmGroupSelect;
    m_MouseMode = mmTool;
    auto newList = entities;
    ResetToOrigin(newList, m_MapOffsetMS);
    m_Entities.insert(m_Entities.end(), newList.begin(), newList.end());
    UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ToggleEntityLocks()
{
    auto update = false;
    for (auto& entity : m_Entities) {
        if (entity.Selected) {
            auto locked = entity.RoomLocked;
            entity.RoomLocked = !entity.RoomLocked;
            update |= entity.RoomLocked != locked;
        }
    }
    if (update) {
        Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SetSpriteType(int type)
{
    auto update = false;
    for (auto& entity : m_Entities) {
        if (entity.IsSprite && entity.Selected) {
            update |= entity.SpriteType != type;
            entity.SpriteType = type;
        }
    }
    if (update) {
        Refresh();
    }
}
//---------------------------------------------------------------------------
bool __fastcall TileEditor::ClearHover()
{
    bool update = false;
    if (m_HoverEntity.Id) {
        auto entity = std::find_if(m_Entities.begin(), m_Entities.end(), [&](const Project::MapEntity& e) { return m_HoverEntity == e; });
        entity->Dirty = true;
        update = true;
    }
    m_HoverEntity.Clear();
    return update;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SelectHover()
{
    UnselectAll();
    auto entity = std::find_if(m_Entities.begin(), m_Entities.end(), [&](const Project::MapEntity& e) { return m_HoverEntity == e; });
    entity->Selected = true;
    m_SelectionCount = 1;
    m_HoverEntity.Clear();
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::UnselectAll(bool update)
{
    m_SelectionCount = 0;
    ToolEntity = 0;
    for (auto& e : m_Entities) {
        e.Selected = false;
        e.Dirty = true;
    }
    if (update) {
        Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::SelectRoom(TPoint room)
{
    m_SelectedRoom = room;
    UnselectAll(false);
    Bus::Publish<RoomSelected>(RoomSelected(room));
    UpdateMap();
}
//---------------------------------------------------------------------------
int __fastcall TileEditor::Snap(int value, int range) const
{
    return static_cast<int>(value / range) * range;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::ReplaceEntities()
{
    for (auto& e : m_ToolEntities) {
        // remove the existing entity at the location
        m_Entities.erase(std::remove_if(m_Entities.begin(),m_Entities.end(),
            [&](const Project::MapEntity& entity) { return entity.Type == e.Type && entity.Pt.x == e.Pt.x && entity.Pt.y == e.Pt.y; }), m_Entities.end());
        // add the new entity at the location
        m_Entities.push_back(e);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TileEditor::GetEntityUnderMouse(int X, int Y, Project::MapEntity& entity, Visuals::ImageTypes imageType, bool selectIt)
{
    auto pt = ViewToMap(X, Y);
    for (auto& e : m_Entities) {
        if (e.Image->ImageType == imageType) {
            auto ex = e.Pt.x;
            auto ey = e.Pt.y;
            if (ex <= pt.X && pt.X <= ex + e.Image->Width && ey <= pt.Y && pt.Y <= ey + e.Image->Height) {
                e.Selected |= selectIt;
                entity = e;
                return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::AssignRoomIndexes(Project::MapEntityList& entities)
{
    // assign room indexes
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    auto roomSize = TSize(m_Window.Width() * tileSize.cx, m_Window.Height() * tileSize.cy);
    for (auto& e : entities) {
        if (!e.RoomLocked && e.Image->CanBeLocked) {
            auto roomPt = TPoint(static_cast<int>(e.Pt.X / roomSize.cx), static_cast<int>(e.Pt.Y / roomSize.cy));
            e.RoomIndex = FRetrieveRoomIndex(roomPt, e.RoomIndex != Project::g_RoomIndexDisabled);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Copy()
{
    if (m_Mode == temSelect) {
        m_ClipboardEntities.clear();
        m_ClipboardEntities = GetSelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Cut()
{
    if (m_Mode == temSelect) {
        m_ClipboardEntities.clear();
        m_ClipboardEntities = GetSelection();
        DeleteSelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TileEditor::Paste()
{
    if (m_Mode == temSelect) {
        UnselectAll(false);
        Add(m_ClipboardEntities);
    }
}
//---------------------------------------------------------------------------

