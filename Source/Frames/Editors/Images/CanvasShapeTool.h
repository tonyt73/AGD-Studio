//---------------------------------------------------------------------------
#ifndef CanvasShapeToolH
#define CanvasShapeToolH
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
class CanvasShapeTool : public CanvasTool
{
private:
    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt) override;

            void    __fastcall  DrawRectangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill);
            void    __fastcall  DrawEllipse(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill);
            void    __fastcall  DrawDiamond(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill);
            void    __fastcall  DrawTriangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill);
            void    __fastcall  DrawRightTriangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill);

public:
                    __fastcall  CanvasShapeTool();
};
//---------------------------------------------------------------------------
#endif

