param (
    [String]$File = "..\AGD Studio.cbproj",
    [Switch]$Major,
    [Switch]$Minor,
    [Switch]$Patch
)

Set-Location $PSScriptRoot

$newLines = @()
if (Test-Path -Path $File) {
    $lines = Get-Content -Path $File
    $tag = "ProductVersion="
    $lines.ForEach({
        if ($_.Contains($tag)) {
            $sp = $_.IndexOf($tag)
            $ep = $_.IndexOf(";", $sp + $tag.Length)
            $ep = $ep -gt $sp ? $ep : $_.Length
            $vp = $sp + $tag.Length
            $version = $_.Substring($vp, $ep - $vp)
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
            $_ = $_.Substring(0, $vp) + $version + $_.Substring($ep, $_.Length - $ep)
        }
        $newLines += $_
    })
    $newLines | Set-Content $File
}

