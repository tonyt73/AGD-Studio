//---------------------------------------------------------------------------
#ifndef WindowDocumentH
#define WindowDocumentH
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
                TRect       m_Rect;
                TSize       m_SizeInCharacters;
                TSize       m_SizeInPixels;

                void        DoSave();
                void        OnLoaded();
    __fastcall  int         Get(int index);
public:
                            WindowDocument(const String& name);

    static      Document*   Create(const String& name, const String& extra) { return new WindowDocument(name); };
                void        Set(const TRect& rect);

    __property const TRect& Rect        = { read = m_Rect         };

__published:
    __property  int         Left        = { read = Get, index = 0 };
    __property  int         Top         = { read = Get, index = 1 };
    __property  int         Right       = { read = Get, index = 2 };
    __property  int         Bottom      = { read = Get, index = 3 };
    __property  int         Width       = { read = Get, index = 4 };
    __property  int         Height      = { read = Get, index = 5 };
    __property  int         Columns     = { read = Get, index = 6 };
    __property  int         Rows        = { read = Get, index = 7 };
    __property  int         PixelsWidth = { read = Get, index = 8 };
    __property  int         PixelsHeight= { read = Get, index = 9 };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
