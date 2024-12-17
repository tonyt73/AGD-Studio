//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "MapPencilTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapPencilTool::MapPencilTool()
: MapTool()
{
    Flags = modifies;
}
//---------------------------------------------------------------------------
__fastcall MapPencilTool::~MapPencilTool()
{
}
//---------------------------------------------------------------------------
void __fastcall MapPencilTool::Apply(Project::MapEntityList& list, Project::MapEntity entity)
{
    SnapToTileGrid(LastPt);
    entity.Pt = LastPt;
    Set(list, entity);
}
//---------------------------------------------------------------------------
