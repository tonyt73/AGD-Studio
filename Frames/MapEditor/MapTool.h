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
protected:
                                // draw functions
            void    __fastcall  DrawLine(EntityList& list, const TRect& Rect, LinePositions* ptList);
            void    __fastcall  DrawHLine(EntityList& list, int xs, int xe, int y);

public:
                    __fastcall  MapTool();
                    __fastcall ~MapTool();
};
//---------------------------------------------------------------------------
#endif
