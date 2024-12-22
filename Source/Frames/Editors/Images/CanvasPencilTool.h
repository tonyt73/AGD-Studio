//---------------------------------------------------------------------------
#ifndef CanvasPencilToolH
#define CanvasPencilToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasPencilTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt) override;

public:
                    __fastcall  CanvasPencilTool();
};
//---------------------------------------------------------------------------
#endif
