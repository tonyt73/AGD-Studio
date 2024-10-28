//---------------------------------------------------------------------------
#ifndef CanvasLineToolH
#define CanvasLineToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasLineTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt);

public:
                    __fastcall  CanvasLineTool();
    virtual         __fastcall ~CanvasLineTool();
};
//---------------------------------------------------------------------------
#endif

