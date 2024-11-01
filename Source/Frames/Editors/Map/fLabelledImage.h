//---------------------------------------------------------------------------
#ifndef fLabelledImageH
#define fLabelledImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Project/Documents/Images.h"
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

private:    // User declarations
                TNotifyEvent            FOnClick;
                Project::ImageDocument* m_Document;
    const       Visuals::GraphicsMode&  m_GraphicsMode;     // the graphics mode used by the project
                bool                    m_Selected;

                void        __fastcall  SetSelected(bool state);
                void        __fastcall  SetShowCaption(bool state);
                void        __fastcall  SetImage(Project::ImageDocument* document);

public:        // User declarations
                                        TfrmLabelledImage(TComponent* Owner);

    __property  bool                    Selected        = { read = m_Selected, write = SetSelected };
    __property  Project::ImageDocument* Image           = { read = m_Document, write = SetImage    };
    __property  bool                    ShowCaption     = { write = SetShowCaption                 };

                void        __fastcall  Update();

            // click events
   __property   TNotifyEvent            OnSelectedClick = { read = FOnClick  , write = FOnClick    };
};
//---------------------------------------------------------------------------
#endif
