@rem
@rem Build New Major script
@rem 

@echo off
@cls

@title "Build New Major Release"

@rem Update the Version
@Powershell.exe -executionpolicy bypass -Command "& '.\Versioner.ps1' -File '..\Source\AGD Studio.cbproj' -patch"

@call Build.bat
