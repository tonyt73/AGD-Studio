//---------------------------------------------------------------------------
#ifndef fLabelledImageH
#define fLabelledImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Project/Documents/BaseImage.h"
#include "Visuals/GraphicsMode.h"
//---------------------------------------------------------------------------
class TfrmLabelledImage : public TFrame
{
__published:    // IDE-managed Components
    TImage *imgImage;
    TLabel *lblCaption;
    TPanel *panImage;
    TPanel *panTileType;
    void __fastcall imgImageClick(TObject *Sender);
    void __fastcall imgImageDblClick(TObject *Sender);

private:        // User declarations
                TNotifyEvent            FOnClick;
                TNotifyEvent            FOnDblClick;
                Project::ImageDocument* m_Document;
    const       Visuals::GraphicsMode&  m_GraphicsMode;     // the graphics mode used by the project
                bool                    m_Selected;

                void        __fastcall  SetSelected(bool state);
                void        __fastcall  SetShowCaption(bool state);
                void        __fastcall  SetImage(Project::ImageDocument* document);

public:        // User declarations
                                        TfrmLabelledImage(TComponent* Owner);

                void        __fastcall  Update();

    __property  bool                    Selected        = { read = m_Selected , write = SetSelected };
    __property  Project::ImageDocument* Image           = { read = m_Document , write = SetImage    };
    __property  bool                    ShowCaption     = { write = SetShowCaption                  };

                // click events
   __property   TNotifyEvent            OnSelectedClick = { read = FOnClick   , write = FOnClick    };
   __property   TNotifyEvent            OnDoubleClick   = { read = FOnDblClick, write = FOnDblClick };
};
//---------------------------------------------------------------------------
#endif
