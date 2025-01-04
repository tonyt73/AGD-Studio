//---------------------------------------------------------------------------
#ifndef MouseStateH
#define MouseStateH
//---------------------------------------------------------------------------
class MouseState
{
private:
    TShiftState m_ShiftState;
    // shift keys
    bool        m_Alt;
    bool        m_AltShift;
    bool        m_Ctrl;
    bool        m_Shift;
    bool        m_NoModifiers;
    // buttons
    bool        m_Left;
    bool        m_Middle;
    bool        m_Right;
public:
            __fastcall  MouseState();
            __fastcall  MouseState(TMouseButton button, const TShiftState& shiftState);
            __fastcall  MouseState(const TShiftState& shiftState);

    bool    __fastcall  Has(TShiftState ss) const;

    __property  bool    Shift       = { read = m_Shift       };
    __property  bool    Ctrl        = { read = m_Ctrl        };
    __property  bool    Alt         = { read = m_Alt         };
    __property  bool    AltShift    = { read = m_AltShift    };
    __property  bool    Left        = { read = m_Left        };
    __property  bool    Middle      = { read = m_Middle      };
    __property  bool    Right       = { read = m_Right       };
    __property  bool    NoModifiers = { read = m_NoModifiers };
};
//---------------------------------------------------------------------------
#endif
