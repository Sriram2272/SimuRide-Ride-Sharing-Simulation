param(
    [string]$BuildDir = "build"
)
if (-not (Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }
Push-Location $BuildDir
cmake ..
cmake --build . --config Release
Pop-Location
