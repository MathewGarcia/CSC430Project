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

4. **Third-Party Libraries**:  
   - The project depends on the following third-party libraries:
     - **CURL**
     - **Zlib**
     - **OpenSSL**
   - These dependencies are located in the `third_party` directory within the project. The `setup.bat` script handles their configuration and linking.

---

## Cloning the Repository

If you have not yet cloned the repository, follow these steps to clone the **CURL-GUI** branch using Git Bash on your Windows PC:

1. **Open Git Bash**:  
   - You can find Git Bash by searching for it in the Start menu.

2. **Navigate to Your Desired Directory**:  
   - To clone the repository directly to your Desktop, enter the following command:
     ```bash
     cd ~/Desktop
     ```

3. **Clone the CURL-GUI Branch**:  
   - Use the following command to clone the specific branch:
     ```bash
     git clone -b CURL-GUI https://github.com/MathewGarcia/CSC430Project
     ```
   - This command clones the **CURL-GUI** branch of the repository to your current directory.

4. **Verify the Cloning**:  
   - After cloning, ensure that the **CSC430Project** folder appears on your Desktop (or the directory you chose).

---

## Setting Up the Project

1. **Open the Project Folder**:  
   - Navigate to the location where you cloned the repository.  
   - The folder name will be `CSC430Project`.

2. **Run the Setup Script**:  
   - Find the file named `setup.bat` in the project folder.  
   - **Double-click the file** to run it.  
   - The script will:
     - Clean any old files.
     - Configure the project for **Visual Studio** in **Release mode**.
     - Build the project automatically.
     - Open the project in Visual Studio.  
   - **Note**: The script should open the Command Prompt and handle the build process automatically. You may see three yellow warning messages during the setup—these can be safely ignored.
   - Wait for the script to finish. It will display `Setup complete` when done.

---

## What to Do After Setup

1. **If Visual Studio Doesn’t Open Automatically**:  
   - Open the folder named `build` inside the project directory.  
   - Double-click the file `CSC430Project.sln` to open the project in Visual Studio.

2. **Running the Project**:  
   - In Visual Studio, ensure the configuration (top toolbar) is set to **Release**.  
     - You can select it from a dropdown menu if it isn’t already selected.  
   - Since the project is already built by the `setup.bat` script, you can directly run the project:  
     - Press `F5` or click the `Start` button in Visual Studio to run the application.

---

## Troubleshooting

- **I Don’t See the `setup.bat` File.**  
  Ensure that you are in the correct project folder. Verify that you cloned the correct branch (**CURL-GUI**) from the repository.

- **The Script Shows Errors During Setup.**  
  Verify that **CMake** and **Visual Studio 2022** are installed and added to your PATH.  
  You can verify their installation by typing these commands in "Command Prompt":
  - `cmake --version` (to check CMake)
  - `MSBuild.exe -version` (to check MSBuild)

- **I Need to Copy the Output from the Command Prompt.**  
  Highlight the output with your mouse, right-click to copy, and paste it where needed. The setup script does not modify or enable Quick Edit Mode.

- **Build Errors Related to Third-Party Libraries.**  
  Ensure that the `third_party` directory contains the required libraries (`curl`, `zlib`, `openssl`). If they are missing, rerun the `setup.bat` script or manually verify the presence of these directories and their respective `include` and `lib` folders.

- **Yellow Warning Messages During Setup.**  
  The setup process may display three yellow warning messages. These are generally harmless and can be safely ignored.

---

## Notes on Branch Names

If the branch name changes from **CURL-GUI**, these instructions will still work. The branch name does not affect the folder name after cloning.

---
