# CSC430Project - CURL-GUI Branch

## Prerequisites

1. **CMake**:  
   - CMake is used to configure the project.  
   - It is included with Visual Studio 2022 and usually added to your system PATH automatically during installation.  
   - **To check if CMake is installed**:  
     - Open "Command Prompt" or "PowerShell".  
     - Type `cmake --version` and press Enter.  
     - If CMake is installed, its version number will appear. If not, download it from [cmake.org](https://cmake.org/).

2. **Visual Studio 2022**:  
   - Required for building and running the project.  
   - During installation, select the **"Desktop Development with C++"** workload.  
   - **To check if MSBuild (part of Visual Studio) is installed**:  
     - Open "Command Prompt" or "PowerShell".  
     - Type `MSBuild.exe -version` and press Enter.  
     - If installed, a version number will be displayed.

3. **Git**:  
   - Git is used to clone the repository. If you are reading this file, you’ve already cloned the repository. If not, download Git from [git-scm.com](https://git-scm.com/).

---

## Setting Up the Project

1. Open the folder where the project is located.  
   - If you cloned the `CURL-GUI` branch, the folder name will match the repository name:  
     `CSC430Project`.  
   - The branch name does not affect the folder name.

2. Run the setup script:  
   - Find the file named `setup.bat` in the project folder.  
   - **Double-click the file** to run it.  
   - The script will:
     - Clean any old files.
     - Configure the project for **Visual Studio** in **Release mode**.
     - Build the project.
     - Automatically open the project in Visual Studio.  
   - Wait for the script to finish. It will display `Setup complete` when done.

---

## What to Do After Setup

1. If Visual Studio doesn’t open automatically:  
   - Open the folder named `build` inside the project directory.  
   - Double-click the file `CSC430Project.sln` to open the project in Visual Studio.

2. Building and running the project:  
   - In Visual Studio, ensure the configuration (top toolbar) is set to **Release**.  
     - You can select it from a dropdown menu if it isn’t already selected.  
   - Click `Build > Build Solution` in the Visual Studio menu.  
   - Once the build is complete, you can run the project.

---

## Troubleshooting

- **I don’t see the `setup.bat` file.**  
  Ensure that you are in the correct project folder. Verify that you cloned the correct branch (`CURL-GUI`) from the repository.

- **The script shows errors during setup.**  
  Verify that **CMake** and **Visual Studio 2022** are installed and added to your PATH.  
  You can verify their installation by typing these commands in "Command Prompt":
  - `cmake --version` (to check CMake)
  - `MSBuild.exe -version` (to check MSBuild)

- **I need to copy the output from the Command Prompt.**  
  Highlight the output with your mouse, right-click to copy, and paste it where needed. The setup script does not modify or enable Quick Edit Mode.

---

## Notes on Branch Names

If the branch name changes from `CURL-GUI`, these instructions will still work. The branch name does not affect the folder name after cloning.
