//---------------------------------------------------------------------------
#ifndef ControlsH
#define ControlsH
//---------------------------------------------------------------------------
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
enum eAgdKey { keyFirst = 0, keyUp = 0, keyDown, keyLeft, keyRight, keyFire1, keyFire2, keyFire3, keyOption1, keyOption2, keyOption3, keyOption4, keyLast };
static const eAgdKey AgdKeys[] = { keyUp, keyDown, keyLeft, keyRight, keyFire1, keyFire2, keyFire3, keyOption1, keyOption2, keyOption3, keyOption4, keyLast };
class ControlsDocument : public Document
{
private:
            std::vector<wchar_t>    m_Keys;
            wchar_t                 m_Key;

            void        __fastcall  DoSave() override;
            void        __fastcall  OnEndObject(const String& object) override;
            void        __fastcall  OnLoading() override;
            void        __fastcall  OnLoaded() override;
            String      __fastcall  Get(int index);
            bool        __fastcall  IsActive() const;
            void        __fastcall  DefaultKeys();

public:
                        __fastcall  ControlsDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String&) { return new ControlsDocument(name); }

        wchar_t         __fastcall  GetAsciiCode(eAgdKey key);
        void            __fastcall  SetAsciiCode(eAgdKey key, wchar_t keyCode);

__published:
   __property  String           Left    = { read = Get, index = keyLeft    };
   __property  String           Right   = { read = Get, index = keyRight   };
   __property  String           Up      = { read = Get, index = keyUp      };
   __property  String           Down    = { read = Get, index = keyDown    };
   __property  String           Fire1   = { read = Get, index = keyFire1   };
   __property  String           Fire2   = { read = Get, index = keyFire2   };
   __property  String           Fire3   = { read = Get, index = keyFire3   };
   __property  String           Option1 = { read = Get, index = keyOption1 };
   __property  String           Option2 = { read = Get, index = keyOption2 };
   __property  String           Option3 = { read = Get, index = keyOption3 };
   __property  String           Option4 = { read = Get, index = keyOption4 };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
