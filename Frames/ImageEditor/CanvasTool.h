//---------------------------------------------------------------------------
#ifndef CanvasToolH
#define CanvasToolH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsBuffers.h"
#include "System/Generic.h"
//---------------------------------------------------------------------------
// A base class for image editor painting tools
//---------------------------------------------------------------------------
class CanvasTool
{
protected:
    enum Flags { usesUndo = 1, modifiesImage = 2, resetImageOnMove = 4 };
    typedef std::vector<TPoint>  LinePositions;

    int                         m_Flags;        // flags for the features the tool supports
    TPoint                      m_Start;        // the start point
    TPoint                      m_Last;         // the last move point
    TShiftState                 m_MouseState;   // the mouse/key states when the operation started
    String                      m_Image;        // the image before the modifications are made
    bool                        m_IsDrawing;    // flag: We are drawing
    Generic                     m_Parameters;   // the parameters specific for each tool

    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt) = 0;
                                // mouse button helpers
            bool    __fastcall  IsLeftDown() const;
            bool    __fastcall  IsRightDown() const;
            bool    __fastcall  IsMiddleDown() const;
            void    __fastcall  DrawLine(Agdx::GraphicsBuffer& canvas, const TRect& Rect, bool set, LinePositions* list = nullptr);
            void    __fastcall  DrawVLine(Agdx::GraphicsBuffer& canvas, int x, int ys, int ye, bool set);
            void    __fastcall  DrawHLine(Agdx::GraphicsBuffer& canvas, int xs, int xe, int y, bool set);

public:
                    __fastcall  CanvasTool();
    virtual         __fastcall ~CanvasTool();

                                // TODO: Set selection rect

                                // parameters
            void    __fastcall  Parameters(const Generic& parameters);

                                // return undo string
            String  __fastcall  Begin(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    __fastcall  Move(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  __fastcall  End(Agdx::GraphicsBuffer& canvas, const TPoint& pt);

};
//---------------------------------------------------------------------------
#endif
