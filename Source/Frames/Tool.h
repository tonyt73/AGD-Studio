//---------------------------------------------------------------------------
#ifndef ToolH
#define ToolH
//---------------------------------------------------------------------------
#include "Frames/MouseState.h"
#include "Services/Generic.h"
//---------------------------------------------------------------------------
class Tool
{
protected:
    // usesUndo     : Uses the undo system
    // modifies     : Modifies the tool surface
    // resetOnMove  : Requires the tool surface to be returned to the original start state
    // allowOnlyOne : Tool only supports one element/entity
    enum eFlags { usesUndo = 1, modifies = 2, resetOnMove = 4, allowOnlyOne = 8 };
    typedef std::vector<TPoint>  LinePositions;

private:

    int                 m_Flags;        // flags for the features the tool supports
    TPoint              m_StartPt;      // the start point
    TPoint              m_LastPt;       // the last move point
    MouseState          m_MouseState;   // the mouse/key states when the operation started
    bool                m_IsDrawing;    // flag: We are drawing
    Services::Generic   m_Parameters;   // the parameters specific for each tool
    int                 m_Width;        // the width of the content we are changing
    int                 m_Height;       // the height of the content we are changing

protected:
    bool                IsPointValid(const TPoint& pt) const;

    void                Begin(const TPoint& pt, const TShiftState& buttons);
    void                Move(const TPoint& pt, const TShiftState& buttons);
    void                End(const TPoint& pt);

    eFlags  __property  Flags = { read = m_Flags, write = m_Flags };
    TPoint  __property  StartPt = { read = m_StartPt, write = StartPt };
    TPoint  __property  LastPt = { read = m_LastPt, write = LastPt };
    bool    __property  IsDrawing = { read = m_IsDrawing, write = m_IsDrawing };

public:
                        Tool();
    virtual            ~Tool();

  Services::Generic __property  Parameters = { read = m_Parameters, write = m_Parameters };
            int     __property  Width      = { read = m_Width     , write = m_Width      };
            int     __property  Height     = { read = m_Height    , write = m_Height     };
  __property  const MouseState& MS         = { read = m_MouseState                       };
};
//---------------------------------------------------------------------------
#endif

