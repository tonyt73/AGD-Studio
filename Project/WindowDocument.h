//---------------------------------------------------------------------------
#ifndef WindowDocumentH
#define WindowDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Event.h"
//---------------------------------------------------------------------------
class WindowDocument : public Document
{
private:
            TRect                   m_Rect;

            void        __fastcall  DoSave();
            void        __fastcall  OnLoaded();
            int         __fastcall  Get(int index);
public:
                        __fastcall  WindowDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new WindowDocument(name); };
            void        __fastcall  Set(const TRect& rect);

           __property  const TRect& Rect   = { read = m_Rect         };

__published:
            int         __property  Left   = { read = Get, index = 0 };
            int         __property  Top    = { read = Get, index = 1 };
            int         __property  Right  = { read = Get, index = 2 };
            int         __property  Bottom = { read = Get, index = 3 };
            int         __property  Width  = { read = Get, index = 4 };
            int         __property  Height = { read = Get, index = 5 };
};
//---------------------------------------------------------------------------
#endif
