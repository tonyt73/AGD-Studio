@rem
@rem Build New Minor script
@rem 

@echo off
@cls

@title "Build New Minor Release"

@rem Update the Version
@Versioner.ps1 -File "..\Source\AGD Studio.cbproj" -minor

@call Build.bat
