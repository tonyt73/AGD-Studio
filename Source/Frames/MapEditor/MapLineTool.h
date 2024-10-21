//---------------------------------------------------------------------------
#ifndef MapLineToolH
#define MapLineToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapLineTool : public MapTool
{
private:
            void      Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
            void      DrawLine(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect);
            void      DrawLine(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect, int dx, int dy);
public:
                      MapLineTool();
    virtual          ~MapLineTool();
};
//---------------------------------------------------------------------------
#endif
