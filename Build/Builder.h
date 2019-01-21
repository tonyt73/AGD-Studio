//---------------------------------------------------------------------------
#ifndef BuilderH
#define BuilderH
//---------------------------------------------------------------------------
#include "BuildMessages.h"
#include "System/File.h"
#include "System/Path.h"
//---------------------------------------------------------------------------
class Builder
{
private:
    String                      m_Description;
    BuildMessageType            m_Type;

protected:
    BuildMessages&              m_BuildMessages;

public:
                    __fastcall  Builder(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~Builder();

    virtual bool    __fastcall  Execute() = 0;

            String  __property  Description = { read = m_Description };
  BuildMessageType  __property  Type = { read = m_Type };
};
//---------------------------------------------------------------------------
#endif
