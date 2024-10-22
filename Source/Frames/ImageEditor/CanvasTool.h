//---------------------------------------------------------------------------
#ifndef CanvasToolH
#define CanvasToolH
//---------------------------------------------------------------------------
#include "Visuals/GraphicsBuffer.h"
#include "../Tool.h"
//---------------------------------------------------------------------------
// A base class for image editor painting tools
//---------------------------------------------------------------------------
class CanvasTool : public Tool
{
protected:
    String          m_Image;        // the image before the modifications are made

    virtual void    Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt) = 0;
            void    DrawLine(Visuals::GraphicsBuffer& canvas, const TRect& Rect, bool set, LinePositions* list = nullptr);
            void    DrawVLine(Visuals::GraphicsBuffer& canvas, int x, int ys, int ye, bool set);
            void    DrawHLine(Visuals::GraphicsBuffer& canvas, int xs, int xe, int y, bool set);

public:
                    CanvasTool();
    virtual        ~CanvasTool();

                                // TODO: Set selection rect

                                // return undo string
            String  Begin(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    Move(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  End(Visuals::GraphicsBuffer& canvas, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
