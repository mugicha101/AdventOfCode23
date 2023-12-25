param([char]$part='A')
if (Test-Path -Path './a.exe') {
    Remove-Item ./a.exe
}
if (Test-Path -Path './main.txt') {
    Remove-Item ./main.txt
}
g++ -O3 -fpermissive -I "C:/eigen-3.4.0/eigen-3.4.0" -DNDEBUG ./main.cpp
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path './a.exe') {
    ./a.exe $part | Tee-Object ./output.txt
}