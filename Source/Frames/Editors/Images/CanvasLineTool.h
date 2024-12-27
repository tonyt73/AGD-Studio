//---------------------------------------------------------------------------
#ifndef CanvasLineToolH
#define CanvasLineToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasLineTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt) override;

public:
                    __fastcall  CanvasLineTool();
};
//---------------------------------------------------------------------------
#endif

