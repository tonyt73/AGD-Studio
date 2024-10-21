//---------------------------------------------------------------------------
#ifndef MapPencilToolH
#define MapPencilToolH
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
//---------------------------------------------------------------------------
class MapPencilTool : public MapTool
{
private:
            void    __fastcall  Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
public:
                    __fastcall  MapPencilTool();
    virtual         __fastcall ~MapPencilTool();
};
//---------------------------------------------------------------------------
#endif
