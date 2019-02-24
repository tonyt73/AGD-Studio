//---------------------------------------------------------------------------
#ifndef ControlsDocumentH
#define ControlsDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class ControlsDocument : public Document
{
private:
        std::vector<unsigned char>  m_Keys;
            unsigned char           m_Key;

            void        __fastcall  DoSave();
            void        __fastcall  OnEndObject(const String& object);
            void        __fastcall  OnLoading();
            String      __fastcall  Get(int index);
            bool        __fastcall  IsActive() const;

public:
                        __fastcall  ControlsDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ControlsDocument(name); };

__published:
        String          __property  Up      = { read = Get, index = 0 };
        String          __property  Down    = { read = Get, index = 1 };
        String          __property  Left    = { read = Get, index = 2 };
        String          __property  Right   = { read = Get, index = 3 };
        String          __property  Fire1   = { read = Get, index = 4 };
        String          __property  Fire2   = { read = Get, index = 5 };
        String          __property  Fire3   = { read = Get, index = 6 };
        String          __property  Option1 = { read = Get, index = 7 };
        String          __property  Option2 = { read = Get, index = 8 };
        String          __property  Option3 = { read = Get, index = 9 };
        String          __property  Option4 = { read = Get, index =10 };
};
//---------------------------------------------------------------------------
#endif
