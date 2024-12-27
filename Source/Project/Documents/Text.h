//---------------------------------------------------------------------------
#ifndef TextH
#define TextH
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
            void        __fastcall  DoSave() override;
public:
                        __fastcall  TextDocument(const String& name);
    virtual             __fastcall ~TextDocument() override {}

    static  Document*   __fastcall  Create(const String& name, const String&) { return new TextDocument(name); }
            void        __fastcall  Add(const String& lines);

            bool        __fastcall  Load() override;
            void        __fastcall  Save() override;
};
//---------------------------------------------------------------------------
class EventDocument final : public TextDocument
{
public:
                        __fastcall  EventDocument(const String& name);
                        __fastcall ~EventDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String&) { return new EventDocument(name); }
};
//---------------------------------------------------------------------------
class MessageDocument final : public TextDocument
{
public:
                        __fastcall  MessageDocument(const String& name);
                        __fastcall ~MessageDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String&) { return new MessageDocument(name); }
};
//---------------------------------------------------------------------------
class SfxDocument final : public TextDocument
{
public:
                        __fastcall  SfxDocument(const String& name);
                        __fastcall ~SfxDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String&) { return new SfxDocument(name); }
};
//---------------------------------------------------------------------------
class AGDDocument final : public TextDocument
{
public:
                        __fastcall  AGDDocument(const String& name);
                        __fastcall ~AGDDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String&) { return new AGDDocument(name); }
};
//---------------------------------------------------------------------------
class AssemblyDocument final : public TextDocument
{
public:
                        __fastcall  AssemblyDocument(const String& name);
                        __fastcall ~AssemblyDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String&) { return new AssemblyDocument(name); }
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
