//---------------------------------------------------------------------------
#ifndef JumpTableDocumentH
#define JumpTableDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Event.h"
//---------------------------------------------------------------------------
class JumpTableDocument : public Document
{
private:
            void        __fastcall  DoSave();
public:
                        __fastcall  JumpTableDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new JumpTableDocument(name); };


__published:
};
//---------------------------------------------------------------------------
#endif
