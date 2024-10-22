//---------------------------------------------------------------------------
#ifndef MapPencilToolH
#define MapPencilToolH
//---------------------------------------------------------------------------
#include "MapTool.h"
//---------------------------------------------------------------------------
class MapPencilTool : public MapTool
{
private:
            void      Apply(Project::MapEntityList& list, Project::MapEntity entity) final;
public:
                      MapPencilTool();
    virtual          ~MapPencilTool();
};
//---------------------------------------------------------------------------
#endif
