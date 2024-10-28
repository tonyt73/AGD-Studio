//---------------------------------------------------------------------------
#ifndef MapRectToolH
#define MapRectToolH
//---------------------------------------------------------------------------
#include "MapTool.h"
//---------------------------------------------------------------------------
class MapRectTool : public MapTool
{
private:
            void    __fastcall  Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
            void    __fastcall  DrawRect(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect);
public:
                    __fastcall  MapRectTool();
    virtual         __fastcall ~MapRectTool();
};
//---------------------------------------------------------------------------
#endif
