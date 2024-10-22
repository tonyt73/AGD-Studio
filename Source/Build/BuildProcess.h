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
                     BuildProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         ~BuildProcess();

    virtual bool     Execute() = 0;

            String  __property  Description = { read = m_Description };
  BuildMessageType  __property  Type = { read = m_Type };
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
