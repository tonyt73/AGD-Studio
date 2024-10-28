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
    String                      m_Description;
    BuildMessageType            m_Type;

protected:
    BuildMessages&              m_BuildMessages;

public:
                    __fastcall  BuildProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~BuildProcess();

    virtual bool    __fastcall  Execute() = 0;

    __property String           Description = { read = m_Description };
    __property BuildMessageType Type        = { read = m_Type        };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
