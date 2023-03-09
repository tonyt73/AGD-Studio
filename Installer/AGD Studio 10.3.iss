;
; AGD Studio Install Setup
;


[Setup]
AppName=AGD Studio
AppVersion=0.12 BETA
DefaultDirName={commonpf}\AGD Studio
DefaultGroupName=AGD Studio
UninstallDisplayIcon={app}\AGD Studio.exe
OutputBaseFilename=AGD Studio Setup
Compression=lzma2
SolidCompression=yes
OutputDir=C:\Users\Kiwi\Documents\Embarcadero\Studio\Projects\AGD Studio\Installer
WizardImageFile=agdxstudio-installer-side.bmp
WizardSmallImageFile=agdxstudio-installer-top.bmp
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
Type: filesandordirs; Name: "{userappdata}\AGDx Studio" 
Type: filesandordirs; Name: "{commondocs}\AGDx Studio" 

[Dirs]
Name: "{commondocs}\AGD Studio\Graphics Modes"
Name: "{commondocs}\AGD Studio\Machines"
Name: "{commondocs}\AGD Studio\Palettes"
Name: "{commondocs}\AGD Studio\Styles"
Name: "{commondocs}\AGD Studio\Images"
Name: "{commondocs}\AGD Studio\Coding Templates"
Name: "{commondocs}\AGD Studio\Compilers\Acorn Atom"
Name: "{commondocs}\AGD Studio\Compilers\Amstrad CPC"
Name: "{commondocs}\AGD Studio\Compilers\Dragon"
Name: "{commondocs}\AGD Studio\Compilers\Enterprise"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2"
Name: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3"
Name: "{commondocs}\AGD Studio\Projects\Foggy"
Name: "{commondocs}\AGD Studio\Common\Saved Palettes"
Name: "{commondocs}\AGD Studio\Projects"

[Files]
; Styling
Source: VclStylesinno.dll; DestDir: {app}; Flags: uninsneveruninstall
Source: "Files\Styles\Windows 10 Black Pearl.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
; x64 (64 bit) application files (Program Files)
Source: "Binaries\Win64\AGD Studio.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\AGDStudio.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\AGD Converter.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\borlndmm.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\cc64260.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\cc64260mt.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtcore260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtdocking260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtelcore260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtelpro260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtinspector260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtlog260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtprint260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtrtlx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\lmdrtsyntax260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\rtl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vcl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vclactnband260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vclimg260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vclsmp260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vclwinx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "Binaries\Win64\vclx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
; x86 (32 bit) application files (Program Files (x86))
Source: "Binaries\Win32\AGD Studio.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "Binaries\Win32\AGDStudio.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\AGD Converter.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\borlndmm.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\cc32c260.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\cc32c260mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\cc32260.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\cc32260mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtcore260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtdocking260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtelcore260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtelpro260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtinspector260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtlog260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtprint260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtrtlx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\lmdrtsyntax260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\rtl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vcl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vclactnband260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vclimg260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vclsmp260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vclwinx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "Binaries\Win32\vclx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
; COMMON FILES
Source: "Files\Common\AGDX Commands.csv"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: solidbreak 
Source: "Files\Common\File Definitions.json"; DestDir: "{commondocs}\AGD Studio\Common";
Source: "Files\Common\Mru.json"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: onlyifdoesntexist uninsneveruninstall
Source: "Files\Common\Settings.json"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: onlyifdoesntexist uninsneveruninstall
; GRAPHICS MODES
Source: "Files\Graphics Modes\Acorn Atom 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Acorn Atom Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Amstrad CPC Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Amstrad CPC Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Amstrad CPC Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\BBC Micro Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\BBC Micro Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\BBC Micro Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\BBC Micro Mode 4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\BBC Micro Mode 5.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Dragon PMODE3.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Dragon PMODE4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Enterprise Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Sam Coupe Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Sam Coupe Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Sega Master System Mode 4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\Sinclair QL Mode 8.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\ZX Spectrum Colour.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\ZX Spectrum Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
Source: "Files\Graphics Modes\ZX Spectrum ULA+.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes" 
; MACHINES
Source: "Files\Machines\Acorn Atom 128x192 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Acorn Atom 256x192 Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Amstrad CPC 160x200 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\BBC Micro 160x256 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\BBC Micro 320x256 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Dragon 128x192 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Dragon 256x192 Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Sam Coupe 256x192 16 Colour Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Sega Master System 256x192 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\Sinclair QL 256x256 8 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\ZX Spectrum 256x192 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
Source: "Files\Machines\ZX Spectrum 256x192 ULA+.json"; DestDir: "{commondocs}\AGD Studio\Machines" 
; PALETTES
Source: "Files\Palettes\Acorn Atom 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Acorn Atom Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Amstrad CPC.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\BBC Micro.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Dragon 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Dragon Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Sam Coupe Mode 1+2.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Sega Master System.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\Sinclair QL 8 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\ZX Spectrum Next 256.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\ZX Spectrum ULA+.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
Source: "Files\Palettes\ZX Spectrum.json"; DestDir: "{commondocs}\AGD Studio\Palettes" 
; UI STYLES
Source: "Files\Styles\Amakrits.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Amethyst Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Aqua Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Aqua Light Slate 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Aqua Light Slate.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Auric.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Calypso LE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Calypso SE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Calypso SLE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Calypso.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Carbon.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Charcoal Dark Slate.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Cobalt XE Media.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Copper Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Copper.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Coral.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Cyan Dusk.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Cyan Night.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Diamond.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Emerald Light Slate.vsf" ; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Emerald.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Flat UI Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles" 
Source: "Files\Styles\Glossy 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Glossy.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Glow.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Golden Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Iceberg Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Jet.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Lavender Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Luna.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Material Oxford Blue SE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Material Oxford Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Metropolis UI Black.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Metropolis UI Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Metropolis UI Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Metropolis UI Green.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Obsidian.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Puerto Rico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Radiant.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Ruby Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Sapphire Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Silver.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Sky 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Sky.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Slate Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Smokey Quartz Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Stellar Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Stellar.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Tablet Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Tablet Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Turquoise Gray.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Vapor.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Wedgewood Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Blue Whale LE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Blue Whale.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Clear Day.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Green.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Malibu.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Purple.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10 Slate Gray.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Styles\Windows 10.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"
Source: "Files\Coding Templates\BouncingEnemy.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\ControlMenuCPC.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\ControlMenuSpectrum.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\FlashingCollectable.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\HorizontalPatrol.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\LaddersAndLevels.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\LaddersAndLevelsEnemyPursuers.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\MainLoopClock.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\MainLoopTimeBar.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\ManicMiner.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\PlayerRocketMan.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\PushableBlocks.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\StaticCollectable.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Coding Templates\VerticalPatrol.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"
Source: "Files\Compilers\Acorn Atom\CompilerAtom.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Acorn Atom" 
Source: "Files\Compilers\Acorn Atom\engine.inc"; DestDir: "{commondocs}\AGD Studio\Compilers\Acorn Atom" 
Source: "Files\Compilers\Amstrad CPC\CompilerCPC.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Amstrad CPC" 
Source: "Files\Compilers\Amstrad CPC\EngineCPC.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\Amstrad CPC" 
Source: "Files\Compilers\Dragon\CompilerDragon.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Dragon" 
Source: "Files\Compilers\Dragon\engine.inc"; DestDir: "{commondocs}\AGD Studio\Compilers\Dragon" 
Source: "Files\Compilers\Enterprise\CompilerEP.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Enterprise" 
Source: "Files\Compilers\Enterprise\EngineEP.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\Enterprise" 
Source: "Files\Compilers\ZX Spectrum\0.7.0\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0" 
Source: "Files\Compilers\ZX Spectrum\0.7.0\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0" 
Source: "Files\Compilers\ZX Spectrum\0.7.2\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2" 
Source: "Files\Compilers\ZX Spectrum\0.7.2\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2" 
Source: "Files\Compilers\ZX Spectrum\0.7.3\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3" 
Source: "Files\Compilers\ZX Spectrum\0.7.3\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3" 
Source: "Files\Images\Acorn Atom.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Acorn Atom2.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Acorn Electron.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Amstrad CPC.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Amstrad CPC2.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\BBC.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\BBC2.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\BBC3.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Dragon.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Sam Coupe.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Spectrum Next.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\Timex.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\ZX Spectrum.png"; DestDir: "{commondocs}\AGD Studio\Images" 
Source: "Files\Images\ZX Spectrum2.png"; DestDir: "{commondocs}\AGD Studio\Images" 
; PASMO
Source: "Files\Compilers\ZX Spectrum\Pasmo\NEWS"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo" 
Source: "Files\Compilers\ZX Spectrum\Pasmo\pasmo.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo" 
Source: "Files\Compilers\ZX Spectrum\Pasmo\pasmodoc.html"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo" 
Source: "Files\Compilers\ZX Spectrum\Pasmo\README"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo" 
; ZX SPIN
Source: "Files\Compilers\ZX Spectrum\Spin\48.ROM"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\128.ROM"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\atapi.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\csw.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\Default.spincfg"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\fdc765.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\Spin.bin"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\Spin.ini"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\SpinNet.cfg"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\szx.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\UnzDll.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\wd1793.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\whatsnew.txt"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\ZipDll.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\zlib1.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\ZXSpin keys.txt"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\ZXSpin.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\ZXSpin.exe.manifest"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
Source: "Files\Compilers\ZX Spectrum\Spin\ZXSpin.hlp"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin" 
; FONTS
Source: "Files\Fonts\Comfortaa-Bold.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Comfortaa-Light.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa Light (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Comfortaa-Regular.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa Regular (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Black.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Black (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Bold.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Bold (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-BoldCondensed.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Bold Condensed (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Light.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Light (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Medium.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Medium (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Regular.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Regular (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "Files\Fonts\Roboto-Thin.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Thin (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
; EXAMPLE PROJECTS
; FOGGY
Source: "Files\Projects\Foggy\Foggy.agdx"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Collect block.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Completed game.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Fell too far.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Game initialisation.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Initialise sprite.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Introduction menu.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Kill player.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Lost game.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Main loop 1.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Main loop 2.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\New high score.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Player control.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Restart screen.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 1.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 2.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 3.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 4.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 5.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 6.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 7.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite type 8.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Controls.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Game Font.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\JumpTable.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 12.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 13.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 14.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 15.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 16.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 17.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 18.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 19.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Object 20.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sprite 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 12.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 13.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 14.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 15.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 16.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 17.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 18.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 19.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 20.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 21.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 22.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 23.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 24.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 25.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 26.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 27.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 28.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 29.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 30.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 31.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 32.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 33.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 34.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 35.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 36.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 37.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 38.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 39.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 40.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 41.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 42.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 43.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 44.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 45.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 46.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 47.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 48.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 49.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 50.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 51.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 52.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 53.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 54.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 55.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 56.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 57.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 58.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 59.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 60.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 61.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 62.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 63.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 64.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 65.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 66.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 67.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 68.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 69.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 70.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 71.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 72.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 73.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 74.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 75.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 76.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 77.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 78.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile 79.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Tile Map.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Window.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Sound effects.sfx"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"
Source: "Files\Projects\Foggy\Messages.txt"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"

[Icons]
Name: "{group}\AGD Studio"; Filename: "{app}\AGDStudio.exe"
Name: "{group}\AGD Converter"; Filename: "{app}\AGD Converter.exe"

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
var
   OldDir, NewDir: String;
begin
  Log('PrepareToInstall() called');
  OldDir := ExpandConstant('{commondocs}') + '\AGDx Studio';
  NewDir := ExpandConstant('{commondocs}') + '\AGD Studio';
  DirectoryCopy(OldDir, NewDir);
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
