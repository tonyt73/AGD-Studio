@rem
@rem Build New Major script
@rem 

@echo off
@cls

@title "Build New Major Release"

@rem Update the Version
@Versioner.exe -cproj "..\AGD Studio.cbproj" -install ".\\" -major -backup

@call Build.cmd
