//---------------------------------------------------------------------------
#ifndef PaintToolH
#define PaintToolH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsBuffers.h"
//---------------------------------------------------------------------------
// A base class for image editor painting tools
//---------------------------------------------------------------------------
class PaintTool
{
protected:
    enum Flags { usesUndo = 1, modifiesImage = 2, resetImageOnMove = 4 };

    int                         m_Flags;        // flags for the features the tool supports
    TPoint                      m_Start;        // the start point
    TPoint                      m_Last;         // the last move point
    TShiftState                 m_MouseState;   // the mouse/key states when the operation started
    String                      m_Image;        // the image before the modifications are made
    bool                        m_IsDrawing;    // flag: We are drawing

    virtual void    __fastcall  Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt) = 0;
                                // mouse button helpers
            bool    __fastcall  IsLeftDown() const;
            bool    __fastcall  IsRightDown() const;
            bool    __fastcall  IsMiddleDown() const;

public:
                    __fastcall  PaintTool();
    virtual         __fastcall ~PaintTool();

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
