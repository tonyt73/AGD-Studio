//---------------------------------------------------------------------------
#ifndef ControlsDocumentH
#define ControlsDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
enum eAgdKey { keyFirst = 0, keyUp = 0, keyDown, keyLeft, keyRight, keyFire1, keyFire2, keyFire3, keyOption1, keyOption2, keyOption3, keyOption4, keyLast };
static const eAgdKey AgdKeys[] = { keyUp, keyDown, keyLeft, keyRight, keyFire1, keyFire2, keyFire3, keyOption1, keyOption2, keyOption3, keyOption4, keyLast };
class ControlsDocument : public Document
{
private:
    std::vector<unsigned char>  m_Keys;
                unsigned char   m_Key;

                void            DoSave();
                void            OnEndObject(const String& object);
                void            OnLoading();
                void            OnLoaded();
    __fastcall  String          Get(int index);
                bool            IsActive() const;
                void            DefaultKeys();

public:
                                ControlsDocument(const String& name);

    static      Document*       Create(const String& name, const String& extra) { return new ControlsDocument(name); };

                unsigned char   GetAsciiCode(eAgdKey key);
                void            SetAsciiCode(eAgdKey key, unsigned char keyCode);

__published:
   __property  String           Left = { read = Get, index = keyLeft };
   __property  String           Right = { read = Get, index = keyRight };
   __property  String           Up = { read = Get, index = keyUp };
   __property  String           Down = { read = Get, index = keyDown };
   __property  String           Fire1 = { read = Get, index = keyFire1 };
   __property  String           Fire2 = { read = Get, index = keyFire2 };
   __property  String           Fire3 = { read = Get, index = keyFire3 };
   __property  String           Option1 = { read = Get, index = keyOption1 };
   __property  String           Option2 = { read = Get, index = keyOption2 };
   __property  String           Option3 = { read = Get, index = keyOption3 };
   __property  String           Option4 = { read = Get, index = keyOption4 };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
