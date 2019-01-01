//---------------------------------------------------------------------------
#ifndef MapToolH
#define MapToolH
//---------------------------------------------------------------------------
#include "Project/MapDocuments.h"
#include "System/Generic.h"
#include "Frames/Tool.h"
//---------------------------------------------------------------------------
class MapTool : public Tool
{
private:
    TSize                       m_TileSize;     // the size in pixels of a tile

protected:
                                // draw functions
            void    __fastcall  Set(EntityList& list, const Entity& entity);
            void    __fastcall  DrawLine(EntityList& list, const Entity& entity, const TRect& Rect, LinePositions* ptList = nullptr);
            void    __fastcall  DrawRect(EntityList& list, const Entity& entity, const TRect& Rect);

public:
                    __fastcall  MapTool();
                    __fastcall ~MapTool();
};
//---------------------------------------------------------------------------
#endif
