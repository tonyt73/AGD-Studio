//---------------------------------------------------------------------------
#ifndef CanvasShapeToolH
#define CanvasShapeToolH
//---------------------------------------------------------------------------
#include "Frames/ImageEditor/CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasShapeTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt);

            void    __fastcall  DrawRectangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawEllipse(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawDiamond(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);
            void    __fastcall  DrawRightTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill);

public:
                    __fastcall  CanvasShapeTool();
    virtual         __fastcall ~CanvasShapeTool();
};
//---------------------------------------------------------------------------
#endif

