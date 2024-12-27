//---------------------------------------------------------------------------
#ifndef fEditorMusicH
#define fEditorMusicH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
class TfrmEditorMusic : public TfrmEditor
{
__published:    // IDE-managed Components
private:        // User declarations
public:         // User declarations
                    __fastcall  TfrmEditorMusic(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
#endif
