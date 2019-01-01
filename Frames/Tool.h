//---------------------------------------------------------------------------
#ifndef ToolH
#define ToolH
//---------------------------------------------------------------------------
#include "System/Generic.h"
//---------------------------------------------------------------------------
class Tool
{
protected:
    enum eFlags { usesUndo = 1, modifies = 2, resetOnMove = 4 };
    typedef std::vector<TPoint>  LinePositions;

private:

    int                         m_Flags;        // flags for the features the tool supports
    TPoint                      m_StartPt;      // the start point
    TPoint                      m_LastPt;       // the last move point
    TShiftState                 m_MouseState;   // the mouse/key states when the operation started
    bool                        m_IsDrawing;    // flag: We are drawing
    Generic                     m_Parameters;   // the parameters specific for each tool

protected:
                                // mouse button helpers
            bool    __fastcall  IsLeftDown() const;
            bool    __fastcall  IsRightDown() const;
            bool    __fastcall  IsMiddleDown() const;

            void    __fastcall  Begin(const TPoint& pt, const TShiftState& buttons);
            void    __fastcall  Move(const TPoint& pt, const TShiftState& buttons);
            void    __fastcall  End(const TPoint& pt);

            eFlags  __property  Flags = { read = m_Flags, write = m_Flags };
            TPoint  __property  StartPt = { read = m_StartPt, write = StartPt };
            TPoint  __property  LastPt = { read = m_LastPt, write = LastPt };
            bool    __property  IsDrawing = { read = m_IsDrawing, write = m_IsDrawing };

public:
                    __fastcall  Tool();
    virtual         __fastcall ~Tool();

            Generic __property  Parameters = { read = m_Parameters, write = m_Parameters };
};
//---------------------------------------------------------------------------
#endif

