param (
    [String]$File = "..\Source\AGD Studio.cbproj",
    [Switch]$Major,
    [Switch]$Minor,
    [Switch]$Patch
)

Set-Location $PSScriptRoot

function ReplaceTag(
    [String]$tag,
    [String]$line)
{
    if ($line.Contains($tag)) {
        $sp = $line.IndexOf($tag)
        $ep = $line.IndexOf(";", $sp + $tag.Length)
        $ep = $ep -gt $sp ? $ep : $line.Length
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
        $line = $line.Substring(0, $vp) + $version + $line.Substring($ep, $line.Length - $ep)
    }
    return $line
}

$newLines = @()
if (Test-Path $File) {
    $lines = Get-Content -Path $File
    $tag = "FileVersion="
    $lines.ForEach({
        $line = ReplaceTag "FileVersion=" $_
        $newLines += ReplaceTag "ProductVersion=" $line
    })
    $newLines | Set-Content $File
}

