//---------------------------------------------------------------------------
#ifndef BuildProcessH
#define BuildProcessH
//---------------------------------------------------------------------------
#include "BuildMessages.h"
#include "Parameterizer.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class BuildProcess
{
private:
    BuildMessageType            m_Type;
    String                      m_Description;

protected:
    BuildMessages&              m_BuildMessages;

public:
                    __fastcall  BuildProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~BuildProcess();

    virtual     int __fastcall  Execute() = 0;

    __property String           Description = { read = m_Description };
    __property BuildMessageType Type        = { read = m_Type        };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
