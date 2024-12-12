@echo off
REM This batch file sets up the project for first-time use in Release mode.

REM 1. Clean up old builds
echo Cleaning old build directory...
if exist build rd /s /q build
mkdir build

REM 2. Navigate to the build directory
cd build

REM Check if CMake is installed in PATH
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo CMake not found. Attempting to download and install it...

    REM Check if PowerShell is available
    set "PowerShellPath="
    for /f "delims=" %%a in ('where powershell') do (
        set "PowerShellPath=%%a"
        REM Once we've found PowerShell, jump out of the loop.
        goto :CheckPowerShell
    )

    REM If the loop finishes without a goto, it means we never found PowerShell.
    echo PowerShell not found. Cannot download CMake.
    exit /b 1

:CheckPowerShell
    if "%PowerShellPath%"=="" (
        echo PowerShell not found. Cannot proceed with CMake installation.
        exit /b 1
    ) else (
        echo PowerShell found at: %PowerShellPath%
    )

    REM Define CMake download URL and output path
    set "CMAKE_URL=https://github.com/Kitware/CMake/releases/download/v3.31.2/cmake-3.31.2-windows-x86_64.msi"
    set "CMAKE_INSTALLER=cmake_installer.msi"

    REM Download the CMake installer using PowerShell
    "%PowerShellPath%" -Command "Invoke-WebRequest -Uri '%CMAKE_URL%' -OutFile '%CMAKE_INSTALLER%'"
    if not exist "%CMAKE_INSTALLER%" (
        echo Failed to download CMake installer. Please check your internet connection.
        exit /b 1
    )

    REM Install CMake silently and add it to PATH
    echo Installing CMake...
    msiexec /i "%CMAKE_INSTALLER%" /quiet ADD_CMAKE_TO_PATH=System
    if %ERRORLEVEL% NEQ 0 (
        echo Failed to install CMake. Please check the installer log.
        exit /b 1
    )

    REM Clean up the installer
    del "%CMAKE_INSTALLER%"
) else (
    echo CMake found in PATH. Skipping installation.
)

REM 3. Run CMake configuration for Visual Studio in Release mode
echo Configuring project with CMake for Visual Studio...
cmake .. -A x64
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed. Check your CMakeLists.txt for errors.
    exit /b 1
)

REM 4. Build the project using MSBuild in Release mode
echo Building the project with MSBuild in Release mode...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo Build failed. Check the output for errors.
    exit /b 1
)

REM 5. Notify the user of completion
echo Setup complete. The project has been built successfully in Release mode!

REM 6. Open the Visual Studio solution if it exists
if exist CSC430Project.sln (
    echo Opening Visual Studio solution...
    start CSC430Project.sln
) else (
    echo Visual Studio solution not found. Please check your setup.
)

pause
