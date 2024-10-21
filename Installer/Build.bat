@rem 
@rem Build script
@rem  

@rem Build Executables

@call "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\rsvars.bat"

chdir ..\Source
msbuild "AGD Studio.cbproj" /t:build /p:config="Release" /p:platform=Win64
@rem msbuild "AGDStudio.cbproj" /t:build /p:config="Release" /p:platform=Win64
msbuild "AGD Studio.cbproj" /t:build /p:config="Release" /p:platform=Win32
@rem msbuild "AGDStudio.cbproj" /t:build /p:config="Release" /p:platform=Win32
copy Binaries\Win32\Release\*.exe ..\Installer\Binaries\Win32\
copy Binaries\Win64\Release\*.exe ..\Installer\Binaries\Win64\

@rem chdir ..\AGD-Viewer
@rem msbuild "AGD Converter.cbproj" /t:build /p:config="Release" /p:platform=Win64
@rem msbuild "AGD Converter.cbproj" /t:build /p:config="Release" /p:platform=Win32
@rem copy Win32\Release\*.exe "..\AGD Studio\Installer\Binaries\32"
@rem copy Win64\Release\*.exe "..\AGD Studio\Installer\Binaries\64"

chdir ..\Installer

@call "Build Installers.bat"
pause