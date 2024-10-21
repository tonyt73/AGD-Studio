//---------------------------------------------------------------------------
#ifndef MapToolH
#define MapToolH
//---------------------------------------------------------------------------
#include "Project/TiledMapDocument.h"
#include "Frames/Tool.h"
//---------------------------------------------------------------------------
class MapTool : public Tool
{
private:
    TSize                       m_TileSize;     // the size in pixels of a tile

protected:
                                // draw functions
            int       Snap(int value, int range) const;
            void      SnapToTileGrid(TPoint& pt) const;
            void      SnapToTileGrid(TRect& rect) const;
    virtual void      Apply(Project::MapEntityList& list, Project::MapEntity entity) = 0;
            void      Set(Project::MapEntityList& list, const Project::MapEntity& entity);

    __property  TSize           TileSize = { read = m_TileSize };

public:
                      MapTool();
    virtual          ~MapTool();

                                // return undo string
            String    Begin(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void      Move(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String    End(Project::MapEntityList& list, Project::MapEntity entity, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
