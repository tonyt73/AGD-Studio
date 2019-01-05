//---------------------------------------------------------------------------
#ifndef MapLineToolH
#define MapLineToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapLineTool : public MapTool
{
private:
            void    __fastcall  Apply(EntityList& list, Entity entity, TPoint pt);
            void    __fastcall  DrawLine(EntityList& list, Entity entity, TRect Rect);
public:
                    __fastcall  MapLineTool();
    virtual         __fastcall ~MapLineTool();
};
//---------------------------------------------------------------------------
#endif
