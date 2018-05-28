//---------------------------------------------------------------------------
#ifndef CanvasShapeToolH
#define CanvasShapeToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasShapeTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt);

            void    __fastcall  DrawRectangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawEllipse(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawDiamond(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawTriangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawRightTriangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);

public:
                    __fastcall  CanvasShapeTool();
                    __fastcall ~CanvasShapeTool();
};
//---------------------------------------------------------------------------
#endif

