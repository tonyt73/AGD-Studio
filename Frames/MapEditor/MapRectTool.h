//---------------------------------------------------------------------------
#ifndef MapRectToolH
#define MapRectToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapRectTool : public MapTool
{
private:
            void    __fastcall  Apply(EntityList& list, Entity entity, TPoint pt);
            void    __fastcall  DrawRect(EntityList& list, Entity entity, TRect Rect);
public:
                    __fastcall  MapRectTool();
    virtual         __fastcall ~MapRectTool();
};
//---------------------------------------------------------------------------
#endif
