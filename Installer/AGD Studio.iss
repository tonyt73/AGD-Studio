;
; AGD Studio Install Setup
;

[Setup]
AppName=AGD Studio
AppVersion=0.15.0
DefaultDirName={commonpf}\AGD Studio
DefaultGroupName=AGD Studio
UninstallDisplayIcon={app}\AGD Studio.exe
OutputBaseFilename=AGD Studio Setup
Compression=lzma2
SolidCompression=yes
OutputDir=.
WizardImageFile=agd-studio-installer-side.bmp
WizardSmallImageFile=agd-studio-installer-top.bmp
WizardStyle=modern
WizardImageStretch=yes
PrivilegesRequired=admin
DisableDirPage=yes
DisableProgramGroupPage=yes
AppPublisher=Tony Thompson

; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[UninstallDelete]
Type: filesandordirs; Name: "{userappdata}\AGD Studio" 
Type: filesandordirs; Name: "{commondocs}\AGD Studio" 

[Dirs]
Name: "{commondocs}\AGD Studio\Coding Templates"
Name: "{commondocs}\AGD Studio\Compilers\Acorn Atom"
Name: "{commondocs}\AGD Studio\Compilers\Amstrad CPC"
Name: "{commondocs}\AGD Studio\Compilers\Dragon"
Name: "{commondocs}\AGD Studio\Compilers\Enterprise"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"
Name: "{commondocs}\AGD Studio\Graphics Modes"
Name: "{commondocs}\AGD Studio\Images"
Name: "{commondocs}\AGD Studio\Keyboards"
Name: "{commondocs}\AGD Studio\Machines"
Name: "{commondocs}\AGD Studio\Palettes"
Name: "{commondocs}\AGD Studio\Projects\Foggy"
Name: "{commondocs}\AGD Studio\Save Palettes\Amstrad CPC Mode 0"
Name: "{commondocs}\AGD Studio\Save Palettes\BBC Micro Mode 1"
Name: "{commondocs}\AGD Studio\Save Palettes\BBC Micro Mode 2"
Name: "{commondocs}\AGD Studio\Save Palettes\ZX Spectrum ULA+"
Name: "{commondocs}\AGD Studio\Styles"

[Files]
; Styling
Source: VclStylesinno.dll; DestDir: {app}; Flags: uninsneveruninstall
Source: "Files\Styles\Windows 10 Black Pearl.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
; x64 (64 bit) application files (Program Files)
Source: "Binaries\Win64\AGD Studio.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\Launcher.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\borlndmm.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\cc64290.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\cc64290mt.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\rtl290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vcl290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vclactnband290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vclimg290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
;Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vclsmp290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
;Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vclwinx290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\vclx290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\xmlrtl290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtcore290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtdocking290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtelcore290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtelpro290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtinspector290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtl290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtlog290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
;Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtprint290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtrtlx290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtsyntax290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\win64\lmdrtshell290.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
; x86 (32 bit) application files (Program Files (x86))
Source: "Binaries\Win32\AGD Studio.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "Binaries\Win32\Launcher.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\borlndmm.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\cc32c290.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\cc32c290mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\cc32290.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\cc32290mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\rtl290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vcl290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vclactnband290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vclimg290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
;Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vclsmp290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
;Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vclwinx290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\vclx290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\xmlrtl290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtcore290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtdocking290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtelcore290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtelpro290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtinspector290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtl290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtlog290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
;Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtprint290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtrtlx290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtsyntax290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "C:\Users\Public\Documents\Embarcadero\Studio\23.0\BPL\lmdrtshell290.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
; DOCUMENTS
Source: "Files\Coding Templates\*.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Common\*.*"; DestDir: "{commondocs}\AGD Studio\Common";
Source: "Files\Compilers\Acorn Atom\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\Acorn Atom" 
Source: "Files\Compilers\Amstrad CPC\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\Amstrad CPC" 
Source: "Files\Compilers\Dragon\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\Dragon" 
Source: "Files\Compilers\Enterprise\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\Enterprise" 
Source: "Files\Compilers\ZX Spectrum\0.7.0\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0" 
Source: "Files\Compilers\ZX Spectrum\0.7.2\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2" 
Source: "Files\Compilers\ZX Spectrum\0.7.3\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3" 
Source: "Files\Compilers\ZX Spectrum\Pasmo\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo" 
Source: "Files\Compilers\ZX Spectrum\Spin\*.*"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Fonts\*.TTF"; DestDir: "{commonfonts}"; FontInstall: "Comfortaa (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Graphics Modes\*.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Images\*.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Keyboards\*.png"; DestDir: "{commondocs}\AGD Studio\Keyboards" 
Source: "Files\Machines\*.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Palettes\*.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Projects\Foggy\*.*"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Saved Palettes\Amstrad CPC Mode 0\*.json"; DestDir: "{commondocs}\AGD Studio\Saved Palettes\Amstrad CPC Mode 0" 
Source: "Files\Saved Palettes\BBC Micro Mode 1\*.json"; DestDir: "{commondocs}\AGD Studio\Saved Palettes\BBC Micro Mode 1" 
Source: "Files\Saved Palettes\BBC Micro Mode 2\*.json"; DestDir: "{commondocs}\AGD Studio\Saved Palettes\BBC Micro Mode 2" 
Source: "Files\Saved Palettes\ZX Spectrum ULA+\*.json"; DestDir: "{commondocs}\AGD Studio\Saved Palettes\ZX Spectrum ULA+" 
Source: "Files\Styles\*.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 

[Icons]
Name: "{group}\AGD Studio"; Filename: "{app}\Launcher.exe"

[Code]
procedure DirectoryCopy(SourcePath, DestPath: string);
var
  FindRec: TFindRec;
  SourceFilePath: string;
  DestFilePath: string;
begin
  if FindFirst(SourcePath + '\*', FindRec) then
  begin
    try
      repeat
        if (FindRec.Name <> '.') and (FindRec.Name <> '..') then
        begin
          SourceFilePath := SourcePath + '\' + FindRec.Name;
          DestFilePath := DestPath + '\' + FindRec.Name;
          if FindRec.Attributes and FILE_ATTRIBUTE_DIRECTORY = 0 then
          begin
            if FileCopy(SourceFilePath, DestFilePath, False) then
            begin
              Log(Format('Copied %s to %s', [SourceFilePath, DestFilePath]));
            end
              else
            begin
              Log(Format('Failed to copy %s to %s', [SourceFilePath, DestFilePath]));
            end;
          end
            else
          begin
            if DirExists(DestFilePath) or CreateDir(DestFilePath) then
            begin
              Log(Format('Created %s', [DestFilePath]));
              DirectoryCopy(SourceFilePath, DestFilePath);
            end
              else
            begin
              Log(Format('Failed to create %s', [DestFilePath]));
            end;
          end;
        end;
      until not FindNext(FindRec);
    finally
      FindClose(FindRec);
    end;
  end
    else
  begin
    Log(Format('Failed to list %s', [SourcePath]));
  end;
end;

function PrepareToInstall(var NeedsRestart: Boolean): String;
begin
  Log('PrepareToInstall() called');
  Result := '';
end;

// Import the LoadVCLStyle function from VclStylesInno.DLL
procedure LoadVCLStyle(VClStyleFile: String); external 'LoadVCLStyleW@files:VclStylesInno.dll stdcall setuponly';
procedure LoadVCLStyle_UnInstall(VClStyleFile: String); external 'LoadVCLStyleW@{app}\VclStylesInno.dll stdcall uninstallonly';
// Import the UnLoadVCLStyles function from VclStylesInno.DLL
procedure UnLoadVCLStyles; external 'UnLoadVCLStyles@files:VclStylesInno.dll stdcall setuponly';
procedure UnLoadVCLStyles_UnInstall; external 'UnLoadVCLStyles@{app}\VclStylesInno.dll stdcall uninstallonly';
 
function InitializeSetup(): Boolean;
begin
  Log('Styling: Extracting Style file');
  ExtractTemporaryFile('Windows 10 Black Pearl.vsf');
  Log('Styling: Loading Style file');
  LoadVCLStyle(ExpandConstant('{tmp}\Windows 10 Black Pearl.vsf'));
  Log('Styling: Done');
  Result := True;
end;

function InitializeUninstall: Boolean;
begin
  Result := True;
  LoadVCLStyle_UnInstall(ExpandConstant('{commondocs}\AGD Studio\Styles\Windows 10 Black Pearl.vsf'));
end;
 
procedure DeinitializeSetup();
begin
  UnLoadVCLStyles;
  Log('Styling: Unload Styles');
end;

procedure DeinitializeUninstall();
begin
  UnLoadVCLStyles_UnInstall;
end;
