# Add-Type -AssemblyName System.Drawing
# $icon = New-Object System.Drawing.Icon("./transform/input.ico")
# $stream = New-Object System.IO.MemoryStream
# $icon.Save($stream)
# $text = [System.Text.Encoding]::ASCII.GetString($stream.ToArray())

# Set-Content -Path "output.txt" -Value $text
# icoファイルをバイト配列として読み込み、それをBase64エンコードしてテキストファイルに書き込む

$filename = "./nekos_ico/" + $args[0] + ".ico"
Write-Host($filename)
$bytes = [System.IO.File]::ReadAllBytes($filename)

$txtname = "./txt/" + $args[0] + ".txt"
[System.IO.File]::WriteAllText($txtname, [System.Convert]::ToBase64String($bytes))

$text = [System.IO.File]::ReadAllText($txtname)
$bytes = [System.Convert]::FromBase64String($text)

$output = $args[0] + ".ico"
[System.IO.File]::WriteAllBytes($output, $bytes)
