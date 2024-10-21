//---------------------------------------------------------------------------
#ifndef MapRectToolH
#define MapRectToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapRectTool : public MapTool
{
private:
            void      Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
            void      DrawRect(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect);
public:
                      MapRectTool();
    virtual          ~MapRectTool();
};
//---------------------------------------------------------------------------
#endif
