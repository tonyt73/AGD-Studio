//---------------------------------------------------------------------------
#ifndef CanvasLineToolH
#define CanvasLineToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasLineTool : public CanvasTool
{
private:
    virtual void      Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt);

public:
                      CanvasLineTool();
    virtual          ~CanvasLineTool();
};
//---------------------------------------------------------------------------
#endif

