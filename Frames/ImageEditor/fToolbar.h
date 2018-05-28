//---------------------------------------------------------------------------
#ifndef fToolbarH
#define fToolbarH
//---------------------------------------------------------------------------
#include "System/Generic.h"
//---------------------------------------------------------------------------
class TfrmToolbar : public TFrame
{
public:
                    __fastcall  TfrmToolbar(TComponent* Owner);

    virtual Generic __fastcall  Parameters() const = 0;
};
//---------------------------------------------------------------------------
#endif
