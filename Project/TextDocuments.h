//---------------------------------------------------------------------------
#ifndef TextDocumentsH
#define TextDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TextDocument : public Document
{
private:
   String               m_Contents;
public:
                        __fastcall  TextDocument();

    static  Document*   __fastcall  Create() { return new TextDocument(); };

            void        __fastcall  Save();
            bool        __fastcall  Load();

    __property  String              Contents = { read = m_Contents, write = m_Contents };
};
//---------------------------------------------------------------------------
class EventDocument : public TextDocument
{
private:

public:
                        __fastcall  EventDocument();

    static  Document*   __fastcall  Create() { return new EventDocument(); };
};
//---------------------------------------------------------------------------
class SfxDocument : public TextDocument
{
private:

public:
                        __fastcall  SfxDocument();
    static  Document*   __fastcall  Create() { return new SfxDocument(); };
};
//---------------------------------------------------------------------------
#endif
