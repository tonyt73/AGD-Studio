
function Sort-File {
    param (
		[Parameter(Mandatory, ParameterSetName = 'Sections', Position = 0)]
		[Parameter(Mandatory, ParameterSetName = 'Headers', Position = 0)]
        [String]$File,
		[Parameter(Mandatory, ParameterSetName = 'Sections', Position = 1)]
		[String]$SplitSectionsBy,
		[Parameter(Mandatory, ParameterSetName = 'Headers', Position = 1)]
		[String]$LineTag,
		[Parameter(Mandatory, ParameterSetName = 'Headers', Position = 2)]
		[String]$LineMustStartWith
    )

    if (Test-Path -Path $File) {
        $lines = Get-Content -Path $File

        # break it into sections
        $preSection = @()
        $postSection = @()
        $sortSection = @()
        $inPreSection = $true
		$inBetween = $false
        $lines.foreach({
			$line = $_
			switch ($PSCmdlet.ParameterSetName) {
				'Sections' {
					if ($line.contains($SplitSectionsBy)) {
						$inPreSection = $false
						$sortSection += $line
					} elseif ($inPreSection) {
						$preSection += $line
					} else {
						$postSection += $line
					}
				}
				'Headers' {
					if ($inPreSection) {
						$preSection += $line
					} elseif ($line.contains($LineTag)) {
						$preSection += $line
						$inPreSection = $false
						$inBetween = $true
					} elseif ($inBetween) {
						if ($line.startsWith($LineMustStartWith)) {
							if ($line.Trim() -ne "") {
								$sortSection += $line
							}
						} else {
							$inBetween = $false
							$postSection += ""
							$postSection += $line
						}
					} else {
						$postSection += $line
					}
				}
			}
        })

        # sort the form resources section
        $sortSection = $sortSection | Sort-Object

        # create a new cbproj file
        #Remove-Item -Path "$($File).old" -ErrorAction Ignore
        #Move-Item -Path $File -Destination "$($File).old" 
        $preSection  | Out-File -FilePath $file -Encoding Ascii
        $sortSection | Out-File -FilePath $file -Append -Encoding Ascii
        $postSection | Out-File -FilePath $file -Append -Encoding Ascii
    }
}

$projFile = Get-ChildItem -Filter "*.cbproj"
Sort-File -File $projFile.FullName -SplitSectionsBy "<FormResources"

$cppFile = Get-ChildItem -Filter "$($projFile.BaseName).cpp"
Sort-File -File $cppFile.FullName -SplitSectionsBy "USEFORM("

$hppFiles = Get-ChildItem -Path "Frames" -Filter "f*.h" -Recurse
$hppFiles.ForEach({
	Sort-File -File $_.FullName -LineTag "__published:" -LineMustStartWith "    "
})
