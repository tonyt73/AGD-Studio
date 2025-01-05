param (
    [String]$File = "..\\AGD Studio.cbproj",
    [Switch]$Major,
    [Switch]$Minor,
    [Switch]$Patch
)

Set-Location $PSScriptRoot

$newLines = @()
if (Test-Path -Path $File) {
   	$lines = Get-Content -Path $File
	$lines.ForEach({
		$tags = @("FileVersion=", "ProductVersion=")
		$line = $_
		ForEach($tag in $tags)
		{
			if ($line.Contains($tag)) {
				$sp = $line.IndexOf($tag)
				$ep = $line.IndexOf(";", $sp + $tag.Length)
				$ep = $ep -gt $sp ? $ep : $line.Length
				$vp = $sp + $tag.Length
				$version = $line.Substring($vp, $ep - $vp)
				Write-Host $version "->" -NoNewline
				$tokens = $version.Split(".")
				if ($Major) {
					$tokens[0] = [Int]$tokens[0] + 1
					$tokens[1] = 0
					$tokens[2] = 0                
				} elseif ($Minor) {
					$tokens[1] = [Int]$tokens[1] + 1
					$tokens[2] = 0                
				} elseif ($Patch) {
					$tokens[2] = [Int]$tokens[2] + 1
				}
				$version = $tokens -Join "."
				Write-Host $version
				$line = $line.Substring(0, $vp) + $version + $line.Substring($ep, $line.Length - $ep)
			}
		}
		$newLines += $line
	})
	$newLines | Set-Content $File
} else {
    Write-Error "File '$File' not found"
}

