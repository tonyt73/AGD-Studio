;
; AGD Studio Install Setup
;

[Setup]
AppName=AGD Studio
AppVersion=0.9 BETA
DefaultDirName={pf}\AGD Studio
DefaultGroupName=AGD Studio
UninstallDisplayIcon={app}\AGD Studio.exe
OutputBaseFilename=AGD Studio Setup
Compression=lzma2
SolidCompression=yes
OutputDir=C:\Users\Kiwi\Documents\Embarcadero\Studio\Projects\AGDx-Studio\Install
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
; x64 (64 bit) application files (Program Files)
Source: "..\Binaries\64\AGD Studio.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\AGDStudio.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\AGD Converter.exe"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\borlndmm.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\cc64260.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\cc64260mt.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtcore260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtdocking260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtelcore260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtelpro260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtinspector260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtlog260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtprint260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtrtlx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\lmdrtsyntax260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\rtl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vcl260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vclactnband260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vclimg260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vclsmp260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vclwinx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
Source: "..\Binaries\64\vclx260.bpl"; DestDir: "{app}"; Check: Is64BitInstallMode
; x86 (32 bit) application files (Program Files (x86))
Source: "..\Binaries\32\AGD Studio.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\Binaries\32\AGDStudio.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\AGD Converter.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\borlndmm.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\cc32c260.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\cc32c260mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\cc32260.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\cc32260mt.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtcore260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtdocking260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtelcore260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtelpro260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtinspector260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtlog260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtprint260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtrtlx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\lmdrtsyntax260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\rtl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vcl260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vclactnband260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vclimg260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vclsmp260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vclwinx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
Source: "..\Binaries\32\vclx260.bpl"; DestDir: "{app}"; Check: not Is64BitInstallMode
; COMMON FILES
Source: "{commondocs}\AGD Studio.Install\Common\AGDX Commands.csv"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: solidbreak external 
Source: "{commondocs}\AGD Studio.Install\Common\File Definitions.json"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: external; 
Source: "{commondocs}\AGD Studio.Install\Common\Mru.json"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: onlyifdoesntexist external uninsneveruninstall
Source: "{commondocs}\AGD Studio.Install\Common\Settings.json"; DestDir: "{commondocs}\AGD Studio\Common"; Flags: onlyifdoesntexist external uninsneveruninstall
; GRAPHICS MODES
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Acorn Atom 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Acorn Atom Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Amstrad CPC Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Amstrad CPC Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Amstrad CPC Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\BBC Micro Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\BBC Micro Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\BBC Micro Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\BBC Micro Mode 4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\BBC Micro Mode 5.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Dragon PMODE3.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Dragon PMODE4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Enterprise Mode 0.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Sam Coupe Mode 1.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Sam Coupe Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Sega Master System Mode 4.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\Sinclair QL Mode 8.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\ZX Spectrum Colour.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\ZX Spectrum Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Graphics Modes\ZX Spectrum ULA+.json"; DestDir: "{commondocs}\AGD Studio\Graphics Modes"; Flags: external 
; MACHINES
Source: "{commondocs}\AGD Studio.Install\Machines\Acorn Atom 128x192 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Acorn Atom 256x192 Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Amstrad CPC 160x200 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\BBC Micro 160x256 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\BBC Micro 320x256 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Dragon 128x192 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Dragon 256x192 Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Sam Coupe 256x192 16 Colour Mode 2.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Sega Master System 256x192 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\Sinclair QL 256x256 8 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\ZX Spectrum 256x192 16 Colour.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Machines\ZX Spectrum 256x192 ULA+.json"; DestDir: "{commondocs}\AGD Studio\Machines"; Flags: external 
; PALETTES
Source: "{commondocs}\AGD Studio.Install\Palettes\Acorn Atom 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Acorn Atom Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Amstrad CPC.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\BBC Micro.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Dragon 4 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Dragon Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Monochrome.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Sam Coupe Mode 1+2.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Sega Master System.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\Sinclair QL 8 Colour.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\ZX Spectrum Next 256.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\ZX Spectrum ULA+.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Palettes\ZX Spectrum.json"; DestDir: "{commondocs}\AGD Studio\Palettes"; Flags: external 
; UI STYLES
Source: "{commondocs}\AGD Studio.Install\Styles\Amakrits.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Amethyst Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Aqua Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Aqua Light Slate 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Aqua Light Slate.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Auric.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Calypso LE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Calypso SE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Calypso SLE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Calypso.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Carbon.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Charcoal Dark Slate.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Cobalt XE Media.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Copper Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Copper.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Coral.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Cyan Dusk.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Cyan Night.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Diamond.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Emerald Light Slate.vsf" ; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Emerald.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Flat UI Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Styles\Glossy 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Glossy.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Glow.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Golden Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Iceberg Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Jet.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Lavender Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Luna.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Material Oxford Blue SE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Material Oxford Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Metropolis UI Black.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Metropolis UI Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Metropolis UI Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Metropolis UI Green.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Obsidian.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Puerto Rico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Radiant.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Ruby Graphite.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Sapphire Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Silver.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Sky 2.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Sky.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Slate Classico.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Smokey Quartz Kamri.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Stellar Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Stellar.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Tablet Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Tablet Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Turquoise Gray.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Vapor.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Wedgewood Light.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Black Pearl.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Blue Whale LE.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Blue Whale.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Blue.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Clear Day.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Dark.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Green.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Malibu.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Purple.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10 Slate Gray.vsf"  ; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Styles\Windows 10.vsf"; DestDir: "{commondocs}\AGD Studio\Styles"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\BouncingEnemy.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\ControlMenuCPC.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\ControlMenuSpectrum.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\FlashingCollectable.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\HorizontalPatrol.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\LaddersAndLevels.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\LaddersAndLevelsEnemyPursuers.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\MainLoopClock.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\MainLoopTimeBar.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\ManicMiner.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\PlayerRocketMan.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\PushableBlocks.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\StaticCollectable.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Coding Templates\VerticalPatrol.AGD"; DestDir: "{commondocs}\AGD Studio\Coding Templates"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Compilers\Acorn Atom\CompilerAtom.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Acorn Atom"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Acorn Atom\engine.inc"; DestDir: "{commondocs}\AGD Studio\Compilers\Acorn Atom"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Amstrad CPC\CompilerCPC.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Amstrad CPC"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Amstrad CPC\EngineCPC.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\Amstrad CPC"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Dragon\CompilerDragon.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Dragon"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Dragon\engine.inc"; DestDir: "{commondocs}\AGD Studio\Compilers\Dragon"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Enterprise\CompilerEP.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\Enterprise"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\Enterprise\EngineEP.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\Enterprise"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.0\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.0\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.0"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.2\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.2\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.2"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.3\CompilerZX.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\0.7.3\EngineZX.asm"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\0.7.3"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Acorn Atom.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Acorn Atom2.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Acorn Electron.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Amstrad CPC.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Amstrad CPC2.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\BBC.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\BBC2.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\BBC3.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Dragon.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Sam Coupe.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Spectrum Next.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\Timex.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\ZX Spectrum.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Images\ZX Spectrum2.png"; DestDir: "{commondocs}\AGD Studio\Images"; Flags: external 
; PASMO
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Pasmo\NEWS"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Pasmo\pasmo.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Pasmo\pasmodoc.html"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Pasmo\README"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Pasmo"; Flags: external 
; ZX SPIN
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\48.ROM"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\128.ROM"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\atapi.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\csw.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\Default.spincfg"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\fdc765.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\Spin.bin"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\Spin.ini"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\SpinNet.cfg"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\szx.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\UnzDll.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\wd1793.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\whatsnew.txt"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\ZipDll.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\zlib1.dll"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\ZXSpin keys.txt"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\ZXSpin.exe"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\ZXSpin.exe.manifest"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
Source: "{commondocs}\AGD Studio.Install\Compilers\ZX Spectrum\Spin\ZXSpin.hlp"; DestDir: "{commondocs}\AGD Studio\Compilers\ZX Spectrum\Spin"; Flags: external 
; FONTS
Source: "..\Fonts\Comfortaa-Bold.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Comfortaa-Light.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa Light (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Comfortaa-Regular.TTF"; DestDir: "{fonts}"; FontInstall: "Comfortaa Regular (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Black.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Black (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Bold.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Bold (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-BoldCondensed.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Bold Condensed (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Light.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Light (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Medium.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Medium (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Regular.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Regular (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
Source: "..\Fonts\Roboto-Thin.TTF"; DestDir: "{fonts}"; FontInstall: "Roboto Thin (Open Type)"; Flags: onlyifdoesntexist uninsneveruninstall fontisnttruetype
; EXAMPLE PROJECTS
; FOGGY
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Foggy.agdx"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Collect block.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Completed game.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Fell too far.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Game initialisation.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Initialise sprite.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Introduction menu.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Kill player.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Lost game.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Main loop 1.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Main loop 2.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\New high score.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Player control.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Restart screen.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 1.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 2.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 3.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 4.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 5.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 6.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 7.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite type 8.event"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Controls.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Game Font.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\JumpTable.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 12.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 13.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 14.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 15.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 16.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 17.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 18.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 19.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Object 20.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sprite 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 1.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 2.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 3.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 4.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 5.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 6.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 7.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 8.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 9.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 10.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 11.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 12.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 13.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 14.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 15.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 16.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 17.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 18.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 19.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 20.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 21.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 22.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 23.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 24.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 25.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 26.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 27.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 28.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 29.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 30.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 31.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 32.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 33.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 34.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 35.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 36.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 37.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 38.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 39.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 40.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 41.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 42.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 43.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 44.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 45.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 46.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 47.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 48.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 49.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 50.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 51.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 52.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 53.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 54.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 55.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 56.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 57.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 58.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 59.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 60.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 61.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 62.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 63.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 64.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 65.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 66.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 67.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 68.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 69.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 70.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 71.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 72.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 73.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 74.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 75.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 76.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 77.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 78.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile 79.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Tile Map.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Window.json"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Sound effects.sfx"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external
Source: "{commondocs}\AGD Studio.Install\Projects\Foggy\Messages.txt"; DestDir: "{commondocs}\AGD Studio\Projects\Foggy"; Flags: external

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

