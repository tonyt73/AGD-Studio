//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Forms/fMain.h"
#include "Project/ProjectManager.h"
#include "Project/Documents/MachineConfig.h"
#include "Project/Documents/Settings.h"
#include "Frames/WelcomeDialog/fWelcomeDialog.h"
#include "Frames/IDE/fIDE.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
: TForm(Owner)
, m_FormView(fvNone)
, m_WelcomeFrame(nullptr)
, m_IDEFrame(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    // check command line parameters
    if (!Services::File::Exists(ParamStr(1))) {
        // create the welcome screen
        if (!theAppSettings.WelcomeSkipOnStartup) {
            ShowWelcomeDialog();
        } else {
            Caption = ApplicationName;
            ShowIDE();
            if (theAppSettings.LoadLastProject && theAppSettings.LastProject.Trim() != "")
            {
                theProjectManager.Open(theAppSettings.LastProject);
            }
        }
    } else {
        Caption = ApplicationName;
        ShowIDE();
        auto path = TDirectory::GetCurrentDirectory();
        auto project = Services::File::NameWithExtension(ParamStr(1));
        theProjectManager.Open(Services::File::Combine(path, project));
    }
    // TODO -cConfig Setup: Remove: Used to generate initial JSON config files
    //auto pw = std::make_unique<PaletteWriter>();
    //auto pw = std::make_unique<GraphicsModeWriter>();
    //auto pw = std::make_unique<MachineConfigWriter>();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormActivate(TObject *Sender)
{
    static bool atStartup = true;
    if (atStartup && theAppSettings.WelcomeSkipOnStartup) {
        // We skipped the Welcome dialog; so finish off the main form setup
        IDE->OnActivate(this);
    }
    atStartup = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    SaveSettings();
    if (m_FormView == fvGameIDE)
    {
        IDE->OnClose();
        OnIDEClose(Sender);
        CanClose = theAppSettings.WelcomeSkipOnClose;
    } else {
        CanClose = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
    Welcome->OnActivate(nullptr);
    IDE->OnActivate(nullptr);
    m_FormView = fvNone;
    m_IDEFrame = nullptr;
    m_WelcomeFrame = nullptr;
}
//---------------------------------------------------------------------------
TAppFrame* __fastcall TfrmMain::GetWelcome()
{
    if (m_WelcomeFrame == nullptr) {
        m_WelcomeFrame = std::make_unique<TfrmWelcomeDialog>(this);
    }
    return m_WelcomeFrame.get();
}
//---------------------------------------------------------------------------
TAppFrame* __fastcall TfrmMain::GetIDE()
{
    if (m_IDEFrame == nullptr) {
        m_IDEFrame = std::make_unique<TfrmIDE>(this);
        //theProjectManager.Initialise(m_IDEFrame->tvProject);
    }
    return m_IDEFrame.get();
}
//---------------------------------------------------------------------------
TAppFrame* __fastcall TfrmMain::GetActiveForm()
{
    return m_FormView == fvGameIDE ? GetIDE() : GetWelcome();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnIDEClose(TObject *Sender)
{
    if (!theAppSettings.WelcomeSkipOnClose) {
        // show the welcome screen
        ShowWelcomeDialog();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnWelcomeDone(TObject *Sender)
{
    // show the IDE
    if (Sender) {
        ShowIDE();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowWelcomeDialog()
{
    m_FormView = fvNone;
    Welcome->OnDone  = OnWelcomeDone;
    Welcome->OnActivate(this);
    BorderIcons = TBorderIcons() << biMinimize << biSystemMenu;
    AutoSize = true;
    BorderStyle = bsSingle;
    Menu = nullptr;
    WindowState = wsNormal;
    // let the above setting be applied
    Application->ProcessMessages();
    // then we can change the position
    Left = theAppSettings.WelcomePosition.X;
    Top  = theAppSettings.WelcomePosition.Y;
    if (Left == 0 && Top == 0) {
        Position = poScreenCenter;
    }
    IDE->OnFormClose = OnIDEClose;
    IDE->OnActivate(nullptr);
    m_FormView  = fvWelcomeDialog;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowIDE()
{
    theAppSettings.WelcomePosition = TPoint(Left, Top);
    Welcome->OnActivate(nullptr);
    IDE->OnActivate(this);
    m_FormView = fvNone;
    AutoSize = false;
    BorderIcons = TBorderIcons() << biMaximize << biMinimize << biSystemMenu;
    BorderStyle = bsSizeable;
    // start the IDE up
    WindowState = wsNormal;
    Application->ProcessMessages();
    Left        = theAppSettings.WindowPosition.X;
    Top         = theAppSettings.WindowPosition.Y;
    Width       = theAppSettings.WindowSize.Width;
    Height      = theAppSettings.WindowSize.Height;
    WindowState = theAppSettings.WindowState;
    m_FormView  = fvGameIDE;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SaveSettings()
{
    if (m_FormView == fvGameIDE)
    {
        theAppSettings.WindowState = WindowState;
        if (WindowState == wsNormal)
        {
            theAppSettings.WindowPosition = TPoint(Left, Top);
            theAppSettings.WindowSize     = TSize(Width, Height);
        }
    }
    else if (m_FormView == fvWelcomeDialog)
    {
        TPoint pt(Left, Top);
        theAppSettings.WelcomePosition = pt;
    }
    theAppSettings.Save();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormBeforeMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI)
{
    // don't show window updates while the forms and components are getting DPI resized
    SendMessage(Handle, WM_SETREDRAW, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormAfterMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI)
{
    // show the DPI resize changes
    SendMessage(Handle, WM_SETREDRAW, 1, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize)
{
    if (m_FormView == fvGameIDE && WindowState == wsNormal) {
        theAppSettings.WindowPosition = TPoint(Left, Top);
        theAppSettings.WindowSize     = TSize(Width, Height);
    }
    Resize = true;
}
//---------------------------------------------------------------------------

