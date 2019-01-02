//---------------------------------------------------------------------------
#ifndef CanvasPencilToolH
#define CanvasPencilToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasPencilTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt);

public:
                    __fastcall  CanvasPencilTool();
    virtual         __fastcall ~CanvasPencilTool();
};
//---------------------------------------------------------------------------
#endif
