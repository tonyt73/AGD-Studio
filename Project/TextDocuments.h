//---------------------------------------------------------------------------
#ifndef TextDocumentsH
#define TextDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Event.h"
//---------------------------------------------------------------------------
class TextDocument : public Document
{
private:
            void        __fastcall  DoSave();
public:
                        __fastcall  TextDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TextDocument(name); };
            void        __fastcall  Add(const String& lines);

            bool        __fastcall  Load();
};
//---------------------------------------------------------------------------
class EventDocument : public TextDocument
{
public:
                        __fastcall  EventDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new EventDocument(name); };
};
//---------------------------------------------------------------------------
class MessageDocument : public TextDocument
{
public:
                        __fastcall  MessageDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new MessageDocument(name); };
};
//---------------------------------------------------------------------------
class SfxDocument : public TextDocument
{
public:
                        __fastcall  SfxDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new SfxDocument(name); };
};
//---------------------------------------------------------------------------
class AGDDocument : public TextDocument
{
public:
                        __fastcall  AGDDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new AGDDocument(name); };
};
//---------------------------------------------------------------------------
#endif
