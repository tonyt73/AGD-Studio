//---------------------------------------------------------------------------
#ifndef ControlsDocumentH
#define ControlsDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
enum eAgdKey { keyFirst = 0, keyUp = 0, keyDown, keyLeft, keyRight, keyFire1, keyFire2, keyFire3, keyOption1, keyOption2, keyOption3, keyOption4, keyLast };
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

        unsigned char   __fastcall  GetAsciiCode(eAgdKey key);
        void            __fastcall  SetAsciiCode(eAgdKey key, unsigned char keyCode);
};
//---------------------------------------------------------------------------
#endif
