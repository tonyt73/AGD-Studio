if (Test-Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\22.0\CatalogRepository\DOSCommand-11cb\Packages\11AndAbove\cpp") {
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\22.0\CatalogRepository\DOSCommand-11cb\Packages\11AndAbove\cpp\Win32\Release\" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\22.0\hpp\Win32\" -Force -ErrorAction SilentlyContinue
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\22.0\CatalogRepository\DOSCommand-11cb\Packages\11AndAbove\cpp\Win64\Release\" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\22.0\hpp\Win64\" -Force -ErrorAction SilentlyContinue
}

if (Test-Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\23.0\CatalogRepository\DOSCommand-12\Packages\11AndAbove\cpp\") {
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\23.0\CatalogRepository\DOSCommand-12\Packages\11AndAbove\cpp\Win32\Release\*.hpp" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\23.0\hpp\Win32\" -Force -ErrorAction SilentlyContinue
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\23.0\CatalogRepository\DOSCommand-12\Packages\11AndAbove\cpp\Win64\Release\*.hpp" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\23.0\hpp\Win64\" -Force -ErrorAction SilentlyContinue
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\23.0\CatalogRepository\DOSCommand-12\Packages\11AndAbove\cpp\Win32\Release\*.hpp" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\23.0\dcp\Win32\" -Force -ErrorAction SilentlyContinue
    Copy-Item -Path "$Env:USERPROFILE\Documents\Embarcadero\Studio\23.0\CatalogRepository\DOSCommand-12\Packages\11AndAbove\cpp\Win64\Release\*.hpp" -Destination "C:\Users\Public\Documents\Embarcadero\Studio\23.0\dcp\Win64\" -Force -ErrorAction SilentlyContinue
}
