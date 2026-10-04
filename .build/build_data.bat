@echo off
setlocal

set ROOT_DIR=C:\Users\casta\OneDrive\Desktop\vscode\currency-monitor
set GO_DIR=%ROOT_DIR%\data
set LIB_DIR=%ROOT_DIR%\.lib\currency-lib
set LIB_EXE=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\lib.exe

echo Building Go backend (data.dll)...
echo =====================================================

if not exist "%LIB_DIR%" mkdir "%LIB_DIR%"

cd /d "%GO_DIR%" || (echo Cannot cd to %GO_DIR% & pause & exit /b 1)

go build -buildmode=c-shared -o "%LIB_DIR%\data.dll" .
if errorlevel 1 ( echo ERROR: go build failed & pause & exit /b 1 )

cd /d "%ROOT_DIR%" || (echo Cannot cd to %ROOT_DIR% & pause & exit /b 1)

"%LIB_EXE%" /def:data\data.def /out:"%LIB_DIR%\data.lib" /machine:x64
if errorlevel 1 ( echo ERROR: lib.exe failed & pause & exit /b 1 )

echo.
echo GO BUILD SUCCESSFUL
echo   DLL: %LIB_DIR%\data.dll
echo   HDR: %LIB_DIR%\data.h
echo   LIB: %LIB_DIR%\data.lib
pause
endlocal