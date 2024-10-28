//---------------------------------------------------------------------------
#ifndef MapLineToolH
#define MapLineToolH
//---------------------------------------------------------------------------
#include "MapTool.h"
//---------------------------------------------------------------------------
class MapLineTool : public MapTool
{
private:
            void    __fastcall  Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
            void    __fastcall  DrawLine(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect);
            void    __fastcall  DrawLine(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect, int dx, int dy);
public:
                    __fastcall  MapLineTool();
    virtual         __fastcall ~MapLineTool();
};
//---------------------------------------------------------------------------
#endif
