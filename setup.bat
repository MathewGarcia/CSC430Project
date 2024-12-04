@echo off
REM This batch file sets up the project for first-time use.

REM 1. Clean up old builds
echo Cleaning old build directory...
if exist build rd /s /q build
mkdir build

REM 2. Navigate to the build directory
cd build

REM 3. Run CMake configuration for Visual Studio
echo Configuring project with CMake for Visual Studio...
cmake .. -A x64

REM 4. Build the project using MSBuild
echo Building the project with MSBuild...
cmake --build . --config Release

REM 5. Notify user of completion
echo Setup complete. The project has been built successfully!
pause
