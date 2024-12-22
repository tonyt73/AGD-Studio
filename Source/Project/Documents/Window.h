//---------------------------------------------------------------------------
#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include "Document.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class WindowDocument : public Document
{
private:
            TRect                   m_Rect;
            TSize                   m_SizeInCharacters;
            TSize                   m_SizeInPixels;

            void        __fastcall  DoSave() override;
            void        __fastcall  OnLoaded() override;
            int         __fastcall  Get(int index);
public:
                        __fastcall  WindowDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new WindowDocument(name); }
            void        __fastcall  SetRect(const TRect& rect);

           __property  const TRect& Rect        = { read = m_Rect         };

__published:
            int         __property  Left        = { read = Get, index = 0 };
            int         __property  Top         = { read = Get, index = 1 };
            int         __property  Right       = { read = Get, index = 2 };
            int         __property  Bottom      = { read = Get, index = 3 };
            int         __property  Width       = { read = Get, index = 4 };
            int         __property  Height      = { read = Get, index = 5 };
            int         __property  Columns     = { read = Get, index = 6 };
            int         __property  Rows        = { read = Get, index = 7 };
            int         __property  PixelsWidth = { read = Get, index = 8 };
            int         __property  PixelsHeight= { read = Get, index = 9 };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
