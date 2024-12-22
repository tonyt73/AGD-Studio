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
__published:    // IDE-managed Components
    TPanel *panBlock;
    TPanel *panEmpty;
    TShape *Shape1;
    TShape *Shape2;
    TShape *Shape3;
    TShape *Shape4;
    TShape *Shape5;
    TShape *Shape6;
    TSpeedButton *btnCustom;
    TSpeedButton *btnDeadly;
    TSpeedButton *btnFodder;
    TSpeedButton *btnLadder;
    TSpeedButton *btnPlatform;
    TSpeedButton *btnWall;
    void __fastcall btnPlatformClick(TObject *Sender);

private:    // User declarations
    wchar_t             m_BlockType;
    void    __fastcall  SetBlockType(wchar_t type);
public:        // User declarations
            __fastcall  TfrmBlockTypes(TComponent* Owner) override;

    wchar_t __property  BlockType = { read = m_BlockType, write = SetBlockType };
};
//---------------------------------------------------------------------------
#endif
