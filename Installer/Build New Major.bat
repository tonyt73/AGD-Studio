@rem
@rem Build New Major script
@rem 

@echo off
@cls

@title "Build New Major Release"

@rem Update the Version
@pwsh.exe -executionpolicy bypass -Command "& '.\Versioner.ps1' -File '..\Source\AGD Studio.cbproj' -major"

@call Build.cmd
