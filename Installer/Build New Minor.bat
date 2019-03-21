@rem
@rem Build New Minor script
@rem 

@echo off
@cls

@title "Build New Minor Release"

@rem Update the Version
@Versioner.exe -cproj "..\AGD Studio.cbproj" -install ".\\" -minor -backup

@call Build.bat
