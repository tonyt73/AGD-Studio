//---------------------------------------------------------------------------
#ifndef CanvasLineToolH
#define CanvasLineToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasLineTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt);

public:
                    __fastcall  CanvasLineTool();
                    __fastcall ~CanvasLineTool();
};
//---------------------------------------------------------------------------
#endif

