//---------------------------------------------------------------------------
#ifndef MapPencilToolH
#define MapPencilToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapPencilTool : public MapTool
{
private:
            void    __fastcall  Apply(EntityList& list, Entity entity, TPoint pt);
public:
                    __fastcall  MapPencilTool();
    virtual         __fastcall ~MapPencilTool();
};
//---------------------------------------------------------------------------
#endif
