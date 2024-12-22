//---------------------------------------------------------------------------
#ifndef MapPencilToolH
#define MapPencilToolH
//---------------------------------------------------------------------------
#include "MapTool.h"
//---------------------------------------------------------------------------
class MapPencilTool : public MapTool
{
private:
            void    __fastcall  Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
public:
                    __fastcall  MapPencilTool();
};
//---------------------------------------------------------------------------
#endif
