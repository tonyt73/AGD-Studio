//---------------------------------------------------------------------------
#ifndef TextDocumentsH
#define TextDocumentsH
//---------------------------------------------------------------------------
#include "Document.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class TextDocument : public Document
{
private:
            void         DoSave();
public:
                         TextDocument(const String& name);

    static  Document*    Create(const String& name, const String& extra) { return new TextDocument(name); };
            void         Add(const String& lines);

            bool         Load();
            void         Save();
};
//---------------------------------------------------------------------------
class EventDocument : public TextDocument
{
public:
                         EventDocument(const String& name);

    static  Document*    Create(const String& name, const String& extra) { return new EventDocument(name); };
};
//---------------------------------------------------------------------------
class MessageDocument : public TextDocument
{
public:
                         MessageDocument(const String& name);

    static  Document*    Create(const String& name, const String& extra) { return new MessageDocument(name); };
};
//---------------------------------------------------------------------------
class SfxDocument : public TextDocument
{
public:
                         SfxDocument(const String& name);
    static  Document*    Create(const String& name, const String& extra) { return new SfxDocument(name); };
};
//---------------------------------------------------------------------------
class AGDDocument : public TextDocument
{
public:
                         AGDDocument(const String& name);
    static  Document*    Create(const String& name, const String& extra) { return new AGDDocument(name); };
};
//---------------------------------------------------------------------------
class AssemblyDocument : public TextDocument
{
public:
                         AssemblyDocument(const String& name);
    static  Document*    Create(const String& name, const String& extra) { return new AssemblyDocument(name); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
