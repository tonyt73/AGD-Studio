//---------------------------------------------------------------------------
#ifndef CanvasPencilToolH
#define CanvasPencilToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasPencilTool : public CanvasTool
{
private:
    virtual void    Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt);

public:
                    CanvasPencilTool();
    virtual        ~CanvasPencilTool();
};
//---------------------------------------------------------------------------
#endif
