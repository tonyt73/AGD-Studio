//---------------------------------------------------------------------------
#ifndef fBlockTypesH
#define fBlockTypesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmBlockTypes : public TFrame
{
__published:	// IDE-managed Components
    TPanel *panBlock;
    TPanel *panEmpty;
    TSpeedButton *btnPlatform;
    TSpeedButton *btnWall;
    TSpeedButton *btnLadder;
    TSpeedButton *btnFodder;
    TSpeedButton *btnDeadly;
    TSpeedButton *btnCustom;
    void __fastcall btnPlatformClick(TObject *Sender);
private:	// User declarations
    char        m_BlockType;
public:		// User declarations
            __fastcall  TfrmBlockTypes(TComponent* Owner);

    char    __property  BlockType = { read = m_BlockType };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBlockTypes *frmBlockTypes;
//---------------------------------------------------------------------------
#endif
