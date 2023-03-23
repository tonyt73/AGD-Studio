
function Sort-File {
    param (
        [String]$File,
        [String]$SplitSectionsBy
    )

    if (Test-Path -Path $File) {
        $lines = Get-Content -Path $File

        # break it into sections
        $preSection = @()
        $postSection = @()
        $sortSection = @()
        $inPreSection = $true
        $lines.foreach({
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

        # create a new cbproj file
        Remove-Item -Path "$($File).old" -ErrorAction Ignore
        Move-Item -Path $File -Destination "$($File).old" 
        $preSection | Out-File -FilePath $file
        $sortSection | Out-File -FilePath $file -Append
        $postSection | Out-File -FilePath $file -Append
    }
}

$projFile = Get-ChildItem -Filter "*.cbproj"
Sort-File -File $projFile.FullName -SplitSectionsBy "<FormResources"

$cppFile = Get-ChildItem -Filter "$($projFile.BaseName).cpp"
Sort-File -File $cppFile.FullName -SplitSectionsBy "USEFORM("
