//---------------------------------------------------------------------------
#ifndef MapRectToolH
#define MapRectToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapRectTool : public MapTool
{
private:
            void    __fastcall  Apply(MapEntityList& list, MapEntity entity) final;
            void    __fastcall  DrawRect(MapEntityList& list, MapEntity entity, TRect Rect);
public:
                    __fastcall  MapRectTool();
    virtual         __fastcall ~MapRectTool();
};
//---------------------------------------------------------------------------
#endif
