//---------------------------------------------------------------------------
#ifndef PencilToolH
#define PencilToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/PaintTool.h"
//---------------------------------------------------------------------------
class PencilTool : public PaintTool
{
private:
    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt);

public:
                    __fastcall  PencilTool();
                    __fastcall ~PencilTool();
};
//---------------------------------------------------------------------------
#endif
