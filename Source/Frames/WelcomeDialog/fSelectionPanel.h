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
    TPanel *panProjectInfo;
    TPanel *panRemove;
    TLabel *lblProjectName;
    TLabel *lblProjectPath;
    TImage *imgRemove;
    TLabel *lblMachine;
    TProgressBar *prgLoading;
    TImage *imgLogo;
    TImage *imgOpenProjectFolder;
    void __fastcall panProjectInfoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall lblProjectNameClick(TObject *Sender);
    void __fastcall imgRemoveClick(TObject *Sender);
    void __fastcall imgOpenProjectFolderClick(TObject *Sender);
private:    // User declarations
            // properties
    String              m_Name;
    String              m_Path;
    String              m_Machine;
    bool                m_Selected;
    bool                m_Highlighted;

    void    __fastcall  SetName(String name);
    void    __fastcall  SetPath(String path);
    void    __fastcall  SetMachine(String machine);
    void    __fastcall  SetSelected(bool state);
    void    __fastcall  SetHighlighted(bool state);
    void    __fastcall  SetLoading(bool state);

            // Events
    TNotifyEvent        FOnClick;
    TNotifyEvent        FOnRemoveClick;

public:        // User declarations
            __fastcall  TSelectionPanelFrame(TComponent* Owner);
            __fastcall ~TSelectionPanelFrame();

    void     __fastcall UpdateControl();
    void     __fastcall Tick();

    String  __property  Name = { read = m_Name, write = SetName };
    String  __property  Path = { read = m_Path, write = SetPath };
    String  __property  Machine = { read = m_Machine, write = SetMachine };
    bool    __property  Selected = { read = m_Selected, write = SetSelected };
    bool    __property  Highlighted = { read = m_Highlighted, write = SetHighlighted };
    bool    __property  Loading = { write = SetLoading };

            // click events
            __property  TNotifyEvent OnSelectedClick = { read = FOnClick, write = FOnClick };
            __property  TNotifyEvent OnRemoveClick = { read = FOnRemoveClick, write = FOnRemoveClick };
};
//---------------------------------------------------------------------------
#endif
