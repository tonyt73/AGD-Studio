//---------------------------------------------------------------------------
#ifndef MapLineToolH
#define MapLineToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapLineTool : public MapTool
{
private:
            void    __fastcall  Apply(MapEntityList& list, MapEntity entity) final;
            void    __fastcall  DrawLine(MapEntityList& list, MapEntity entity, TRect Rect);
            void    __fastcall  DrawLine(MapEntityList& list, MapEntity entity, TRect Rect, int dx, int dy);
public:
                    __fastcall  MapLineTool();
    virtual         __fastcall ~MapLineTool();
};
//---------------------------------------------------------------------------
#endif
