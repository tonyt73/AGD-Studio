//---------------------------------------------------------------------------
#ifndef CanvasShapeToolH
#define CanvasShapeToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasShapeTool : public CanvasTool
{
private:
    virtual void    Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt);

            void    DrawRectangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    DrawEllipse(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    DrawDiamond(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    DrawTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    DrawRightTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);

public:
                    CanvasShapeTool();
    virtual        ~CanvasShapeTool();
};
//---------------------------------------------------------------------------
#endif

