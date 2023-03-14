//---------------------------------------------------------------------------
#ifndef BuildProcessH
#define BuildProcessH
//---------------------------------------------------------------------------
#include "Build/BuildMessages.h"
#include "Build/Parameterizer.h"
#include "System/File.h"
#include "System/Path.h"
//---------------------------------------------------------------------------
class BuildProcess
{
private:
    String                      m_Description;
    BuildMessageType            m_Type;

protected:
    BuildMessages&              m_BuildMessages;

public:
                    __fastcall  BuildProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~BuildProcess();

    virtual bool    __fastcall  Execute() = 0;

            String  __property  Description = { read = m_Description };
  BuildMessageType  __property  Type = { read = m_Type };
};
//---------------------------------------------------------------------------
#endif
