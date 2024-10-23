//---------------------------------------------------------------------------
#ifndef fToolbarH
#define fToolbarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "Services/Generic.h"
//---------------------------------------------------------------------------
class TfrmToolbar : public TFrame
{
__published:// IDE-managed Components
private:    // User declarations
public:     // User declarations
    __fastcall TfrmToolbar(TComponent* Owner);

    virtual Services::Generic __fastcall GetParameters() const = 0;
};
//---------------------------------------------------------------------------
#endif
