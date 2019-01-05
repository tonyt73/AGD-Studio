//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapTool::MapTool()
: m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum)
{
}
//---------------------------------------------------------------------------
__fastcall MapTool::~MapTool()
{
}
//---------------------------------------------------------------------------
int __fastcall MapTool::Snap(int value, int range) const
{
    return ((int)(value / range)) * range;
}
//---------------------------------------------------------------------------
void __fastcall MapTool::SnapToTileGrid(TPoint& pt) const
{
    pt.x = Snap(pt.x, m_TileSize.cx);
    pt.y = Snap(pt.y, m_TileSize.cy);
}
//---------------------------------------------------------------------------
void __fastcall MapTool::SnapToTileGrid(TRect& rect) const
{
    rect.Left   = Snap(rect.Left  , m_TileSize.cx);
    rect.Right  = Snap(rect.Right , m_TileSize.cx);
    rect.Top    = Snap(rect.Top   , m_TileSize.cy);
    rect.Bottom = Snap(rect.Bottom, m_TileSize.cy);
}
//---------------------------------------------------------------------------
void __fastcall MapTool::Set(EntityList& list, const Entity& entity)
{
    if (Flags & allowOnlyOne)
    {
        list.clear();
        list.push_back(entity);
    }
    else
    {
        if (IsPointValid(entity.Pt))
        {
            auto it = std::find(list.begin(), list.end(), entity);
            if (it == list.end())
            {
                auto e = entity;
                e.Selected = false;
                list.push_back(e);
            }
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall MapTool::Begin(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons)
{
    Tool::Begin(pt, buttons);
    Apply(list, entity, pt);
    return String();
}
//---------------------------------------------------------------------------
void __fastcall MapTool::Move(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons)
{
    if (entity.Image->SubType != "Tile")
        return;
    Tool::Move(pt, buttons);
    if (!IsDrawing) return;
    Apply(list, entity, pt);
}
//---------------------------------------------------------------------------
String __fastcall MapTool::End(EntityList& list, Entity entity, const TPoint& pt)
{
    if (pt != LastPt)
    {
        Apply(list, entity, pt);
    }
    Tool::End(pt);
    return String();
}
//---------------------------------------------------------------------------

