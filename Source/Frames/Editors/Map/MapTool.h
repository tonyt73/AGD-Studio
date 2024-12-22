//---------------------------------------------------------------------------
#ifndef MapToolH
#define MapToolH
//---------------------------------------------------------------------------
#include "../Tool.h"
#include "Project/Documents/TiledMap.h"
//---------------------------------------------------------------------------
class MapTool : public Tool
{
private:
    TSize                       m_TileSize;     // the size in pixels of a tile

protected:
                                // draw functions
            int     __fastcall  Snap(int value, int range) const;
            void    __fastcall  SnapToTileGrid(TPoint& pt) const;
            void    __fastcall  SnapToTileGrid(TRect& rect) const;
    virtual void    __fastcall  Apply(Project::MapEntityList& list, Project::MapEntity entity) = 0;
            void    __fastcall  Set(Project::MapEntityList& list, const Project::MapEntity& entity);

    __property  TSize           TileSize = { read = m_TileSize };

public:
                    __fastcall  MapTool();

                                // return undo string
            String  __fastcall  Begin(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    __fastcall  Move(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  __fastcall  End(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
