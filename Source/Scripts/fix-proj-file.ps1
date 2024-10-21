function Find-XmlProperty {
    param (
        [String]$File,
        [String]$Property
    )

    if (Test-Path -Path $File) {
        $lines = Get-Content -Path $File
    }
}

function Sort-Lines {
    param (
        [String[]]$Lines,
        [String]$SplitSectionsBy
    )

    # break it into sections
    $preSection = @()
    $postSection = @()
    $sortSection = @()
    $inPreSection = $true
    $Lines.foreach({
        if ($_.contains($SplitSectionsBy)) {
            $inPreSection = $false
            $sortSection += $_
        } elseif ($inPreSection) {
            $preSection += $_
        } else {
            $postSection += $_
        }
    })

    # sort the form resources section
    $sortSection = $sortSection | Sort-Object

    $Lines = $preSection + $sortSection + $postSection
    return $Lines
}

function Sort-File {
    param (
        [String]$File,
        [String]$SplitSectionsBy
    )

    if (Test-Path -Path $File) {
        $lines = Get-Content -Path $File
        Sort-Lines -Lines $lines -SplitSectionsBy $SplitSectionsBy | Out-File -FilePath $File -Encoding Ascii
    }
}


$projFile = Get-ChildItem -Filter "*.cbproj"
# read the file
if (Test-Path -Path $projFile) {
    $lines = Get-Content -Path $projFile
    $lines = Sort-Lines -Lines $lines -SplitSectionsBy "<FormResources"

    # create a new cbproj file
    Remove-Item -Path "$($projFile.BaseName).old" -ErrorAction Ignore
    Move-Item -Path $projFile -Destination "$($projFile.BaseName).old"
    $lines | Out-File -FilePath $projFile -Encoding Ascii

    $cppFile = Get-ChildItem -Filter "$($projFile.BaseName).cpp"
    Sort-File -File $cppFile.FullName -SplitSectionsBy "USEFORM("
	Write-Host "Sorted"
} else {
	Write-Error "File not found"
}