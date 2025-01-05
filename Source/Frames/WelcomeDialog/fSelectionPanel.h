//---------------------------------------------------------------------------
#ifndef SelectionPanelH
#define SelectionPanelH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSelectionPanelFrame : public TFrame
{
__published:// IDE-managed Components
    TImage *imgLogo;
    TImage *imgOpenProjectFolder;
    TImage *imgRemove;
    TLabel *lblMachine;
    TLabel *lblProjectName;
    TLabel *lblProjectPath;
    TPanel *panProjectInfo;
    TPanel *panRemove;
    TProgressBar *prgLoading;
    void __fastcall imgOpenProjectFolderClick(TObject *Sender);
    void __fastcall imgRemoveClick(TObject *Sender);
    void __fastcall lblProjectNameClick(TObject *Sender);
    void __fastcall panProjectInfoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private:    // User declarations
            // properties
    String              m_Name;
    String              m_Path;
    String              m_Machine;
    String              m_Theme;
    bool                m_Selected;
    bool                m_Highlighted;

    void    __fastcall  SetName(String name) override;
    void    __fastcall  SetPath(String path);
    void    __fastcall  SetMachine(String machine);
    void    __fastcall  SetTheme(String folder);
    void    __fastcall  SetSelected(bool state);
    void    __fastcall  SetHighlighted(bool state);
    void    __fastcall  SetLoading(bool state);

            // Events
    TNotifyEvent        FOnClick;
    TNotifyEvent        FOnRemoveClick;

public:        // User declarations
            __fastcall  TSelectionPanelFrame(TComponent* Owner) override;
            __fastcall ~TSelectionPanelFrame() override;

    void     __fastcall UpdateControl();
    void     __fastcall Tick();

    String  __property  Name        = { read  = m_Name       , write = SetName        };
    String  __property  Path        = { read  = m_Path       , write = SetPath        };
    String  __property  Machine     = { read  = m_Machine    , write = SetMachine     };
    String  __property  Theme       = { read  = m_Theme      , write = SetTheme       };
    bool    __property  Selected    = { read  = m_Selected   , write = SetSelected    };
    bool    __property  Highlighted = { read  = m_Highlighted, write = SetHighlighted };
    bool    __property  Loading     = { write = SetLoading                            };

            // click events
            __property  TNotifyEvent OnSelectedClick = { read = FOnClick, write = FOnClick };
            __property  TNotifyEvent OnRemoveClick = { read = FOnRemoveClick, write = FOnRemoveClick };
};
//---------------------------------------------------------------------------
#endif
