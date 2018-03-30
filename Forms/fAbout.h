//---------------------------------------------------------------------------
#ifndef fAboutH
#define fAboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:    // IDE-managed Components
    TImage *imgLogo;
    TLabel *lblTitle1;
    TLabel *lblVersion;
    TLabel *lblCopyright;
    TLabel *lblBuild;
    TShape *shpFrame;
    TLabel *lblAGDCopyright;
    void    __fastcall FormDeactivate(TObject *Sender);
    void    __fastcall FormCreate(TObject *Sender);
private:    // User declarations
    String  __fastcall  DatePlusDays(int days) const;
    void    __fastcall  GetBuildVersion(int& major, int& minor, int& release, int& build) const;

public:        // User declarations
            __fastcall  TfrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
