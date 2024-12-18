//---------------------------------------------------------------------------
#ifndef CanvasToolH
#define CanvasToolH
//---------------------------------------------------------------------------
#include "Visuals/GraphicsBuffer.h"
#include "..\Tool.h"
//---------------------------------------------------------------------------
// A base class for image editor painting tools
//---------------------------------------------------------------------------
class CanvasTool : public Tool
{
protected:
    enum eSavePoints { spNone, spLeft, spRight };
    String                      m_Image;        // the image before the modifications are made
    LinePositions               m_LinePositions;// the line positions of the last DrawLine operation

    virtual void    __fastcall  Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt) = 0;
            void    __fastcall  DrawLine(Visuals::GraphicsBuffer& canvas, const TRect& Rect, bool set, eSavePoints savePoints = spNone);
            void    __fastcall  DrawVLine(Visuals::GraphicsBuffer& canvas, int x, int ys, int ye, bool set);
            void    __fastcall  DrawHLine(Visuals::GraphicsBuffer& canvas, int xs, int xe, int y, bool set);

public:
                    __fastcall  CanvasTool();
    virtual         __fastcall ~CanvasTool();

                                //TODO -cDrawing: Set selection rect

                                // return undo string
            String  __fastcall  Begin(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    __fastcall  Move(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  __fastcall  End(Visuals::GraphicsBuffer& canvas, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
