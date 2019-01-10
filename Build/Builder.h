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
protected:
private:
    BuildMessages&              m_BuildMessages;

public:
                    __fastcall  Builder(BuildMessages& buildMessages);
    virtual         __fastcall ~Builder();

    virtual bool    __fastcall  Execute() = 0;
};
//---------------------------------------------------------------------------
#endif
