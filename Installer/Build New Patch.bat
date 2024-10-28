@rem
@rem Build New Patch script
@rem 

@echo off
@cls

@title "Build New Patch Release"

@rem Update the Version
@pwsh.exe -executionpolicy bypass -Command "& '.\Versioner.ps1' -File '..\Source\AGD Studio.cbproj' -patch"

@call Build.bat
