//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Forms/fMain.h"
#include "Project/ProjectManager.h"
#include "Project/MachineConfig.h"
#include "Settings/Settings.h"
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
    if (!System::File::Exists(ParamStr(1)))
    {
        // create the welcome screen
        if (!appSettings.WelcomeSkipOnStartup)
        {
            ShowWelcomeDialog();
        }
        else
        {
            Caption = ApplicationName;
            ShowIDE();
            if (appSettings.LoadLastProject && appSettings.LastProject.Trim() != "")
            {
                theProjectManager.Open(appSettings.LastProject);
            }
        }
    }
    else
    {
        Caption = ApplicationName;
        ShowIDE();
        auto path = TDirectory::GetCurrentDirectory();
        auto project = System::File::NameWithExtension(ParamStr(1));
        theProjectManager.Open(System::File::Combine(path, project));
    }
    // TODO: Remove: Used to generate initial JSON config files
    //auto pw = std::make_unique<PaletteWriter>();
    //auto pw = std::make_unique<GraphicsModeWriter>();
    //auto pw = std::make_unique<MachineConfigWriter>();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormActivate(TObject *Sender)
{
    static bool atStartup = true;
    if (atStartup && appSettings.WelcomeSkipOnStartup)
    {
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
        // reconstruct the IDE frame
        auto frame = m_IDEFrame.release();
        delete frame;
        m_IDEFrame = nullptr;
        GetIDE();
        CanClose = appSettings.WelcomeSkipOnClose;
    }
    else
    {
        CanClose = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
    Welcome->OnActivate(nullptr);
    IDE->OnActivate(nullptr);
    m_FormView = fvNone;

    m_WelcomeFrame = nullptr;
    m_IDEFrame = nullptr;
}
//---------------------------------------------------------------------------
TfrmWelcomeDialog* __fastcall TfrmMain::GetWelcome()
{
    if (m_WelcomeFrame == nullptr)
    {
        m_WelcomeFrame = std::make_unique<TfrmWelcomeDialog>(this);
    }
    return m_WelcomeFrame.get();
}
//---------------------------------------------------------------------------
TfrmIDE* __fastcall TfrmMain::GetIDE()
{
    if (m_IDEFrame == nullptr)
    {
        m_IDEFrame = std::make_unique<TfrmIDE>(this);
        theProjectManager.Initialise(m_IDEFrame->tvProject);
    }
    return m_IDEFrame.get();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnIDEClose(TObject *Sender)
{
    if (!appSettings.WelcomeSkipOnClose)
    {
        // show the welcome screen
        ShowWelcomeDialog();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnWelcomeDone(TObject *Sender)
{
    // show the IDE
    if (Sender)
    {
        ShowIDE();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowWelcomeDialog()
{
    Welcome->OnDone  = OnWelcomeDone;
    Welcome->OnActivate(this);
    m_FormView  = fvWelcomeDialog;
    BorderIcons = TBorderIcons() << biMinimize << biSystemMenu;
    AutoSize = true;
    BorderStyle = bsSingle;
    Menu = nullptr;
    TPoint pt = appSettings.WelcomePosition;
    Left   = pt.X;
    Top    = pt.Y;
    Width  = Welcome->Width;
    Height = Welcome->Height;
    WindowState = wsNormal;
    if (Left == 0 && Top == 0)
    {
        Position = poScreenCenter;
    }
    IDE->OnFormClose = OnIDEClose;
    IDE->OnActivate(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowIDE()
{
    appSettings.WelcomePosition = TPoint(Left, Top);
    Welcome->OnActivate(nullptr);
    IDE->OnActivate(this);
    m_FormView = fvNone;
    AutoSize = false;
    BorderIcons = TBorderIcons() << biMaximize << biMinimize << biSystemMenu;
    BorderStyle = bsSizeable;
    // start the IDE up
    WindowState = wsNormal;
    Application->ProcessMessages();
    Left        = appSettings.WindowPosition.X;
    Top         = appSettings.WindowPosition.Y;
    Width       = appSettings.WindowSize.Width;
    Height      = appSettings.WindowSize.Height;
    WindowState = appSettings.WindowState;
    m_FormView  = fvGameIDE;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SaveSettings()
{
    if (m_FormView == fvGameIDE)
    {
        appSettings.WindowState = WindowState;
        if (WindowState == wsNormal)
        {
            appSettings.WindowPosition = TPoint(Left, Top);
            appSettings.WindowSize     = TSize(Width, Height);
        }
    }
    else if (m_FormView == fvWelcomeDialog)
    {
        TPoint pt(Left, Top);
        appSettings.WelcomePosition = pt;
    }
}
//---------------------------------------------------------------------------

