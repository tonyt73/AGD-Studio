@rem 
@rem Build script
@rem  

@rem Build Executables

@call "C:\Program Files (x86)\Embarcadero\Studio\20.0\bin\rsvars.bat"

chdir ..
msbuild "AGDx Studio.cbproj" /t:build /p:config="Release" /p:platform=Win64
msbuild "AGDx-Studio.cbproj" /t:build /p:config="Release" /p:platform=Win64
msbuild "AGDx Studio.cbproj" /t:build /p:config="Release" /p:platform=Win32
msbuild "AGDx-Studio.cbproj" /t:build /p:config="Release" /p:platform=Win32
copy Win32\Release\*.exe Binaries\32
copy Win64\Release\*.exe Binaries\64

chdir ..\AGD-Viewer
msbuild "AGD Converter.cbproj" /t:build /p:config="Release" /p:platform=Win64
msbuild "AGD Converter.cbproj" /t:build /p:config="Release" /p:platform=Win32
copy Win32\Release\*.exe ..\AGDx-Studio\Binaries\32\
copy Win64\Release\*.exe ..\AGDx-Studio\Binaries\64\

@rem  Build Installer Packages
chdir ..\AGDx-Studio\Install
"C:\Program Files (x86)\NSIS\makensis.exe" "AGDx Studio 64.nsi"
"C:\Program Files (x86)\NSIS\makensis.exe" "AGDx Studio 32.nsi"
