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
            unsigned char           m_Key;

            void         DoSave();
            void         OnEndObject(const String& object);
            void         OnLoading();
            void         OnLoaded();
            String       Get(int index);
            bool         IsActive() const;
            void         DefaultKeys();

public:
                         ControlsDocument(const String& name);

    static  Document*    Create(const String& name, const String& extra) { return new ControlsDocument(name); };

        unsigned char    GetAsciiCode(eAgdKey key);
        void             SetAsciiCode(eAgdKey key, unsigned char keyCode);

__published:
        String          __property  Left = { read = Get, index = keyLeft };
        String          __property  Right = { read = Get, index = keyRight };
        String          __property  Up = { read = Get, index = keyUp };
        String          __property  Down = { read = Get, index = keyDown };
        String          __property  Fire1 = { read = Get, index = keyFire1 };
        String          __property  Fire2 = { read = Get, index = keyFire2 };
        String          __property  Fire3 = { read = Get, index = keyFire3 };
        String          __property  Option1 = { read = Get, index = keyOption1 };
        String          __property  Option2 = { read = Get, index = keyOption2 };
        String          __property  Option3 = { read = Get, index = keyOption3 };
        String          __property  Option4 = { read = Get, index = keyOption4 };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
