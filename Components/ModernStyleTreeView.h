//---------------------------------------------------------------------------
#ifndef ModernStyleTreeViewH
#define ModernStyleTreeViewH
//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TModernStyleTreeView : public TTreeView
{
protected:
	void __fastcall CreateWnd() override;

public:
	__fastcall TModernStyleTreeView(TComponent* Owner) override;
__published:
};
//---------------------------------------------------------------------------
#endif
