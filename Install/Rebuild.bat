@rem
@rem Build New Major script
@rem 

@echo off
@cls

@title "Rebuild Last Release"

@rem Update the Version
@Versioner.exe -cproj "..\AGDx-Studio.cbproj" -install ".\\"

@call Build.cmd
