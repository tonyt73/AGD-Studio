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
void __fastcall MapPencilTool::Apply(Project::MapEntityList& list, Project::MapEntity entity)
{
    SnapToTileGrid(LastPt);
    entity.Pt = LastPt;
    Set(list, entity);
}
//---------------------------------------------------------------------------
