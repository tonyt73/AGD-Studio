//---------------------------------------------------------------------------
#ifndef CanvasToolH
#define CanvasToolH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsBuffer.h"
#include "System/Generic.h"
#include "Frames/Tool.h"
//---------------------------------------------------------------------------
// A base class for image editor painting tools
//---------------------------------------------------------------------------
class CanvasTool : public Tool
{
protected:
    String                      m_Image;        // the image before the modifications are made

    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt) = 0;
            void    __fastcall  DrawLine(Agdx::GraphicsBuffer& canvas, const TRect& Rect, bool set, LinePositions* list = nullptr);
            void    __fastcall  DrawVLine(Agdx::GraphicsBuffer& canvas, int x, int ys, int ye, bool set);
            void    __fastcall  DrawHLine(Agdx::GraphicsBuffer& canvas, int xs, int xe, int y, bool set);

public:
                    __fastcall  CanvasTool();
    virtual         __fastcall ~CanvasTool();

                                // TODO: Set selection rect

                                // return undo string
            String  __fastcall  Begin(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    __fastcall  Move(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  __fastcall  End(Agdx::GraphicsBuffer& canvas, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
