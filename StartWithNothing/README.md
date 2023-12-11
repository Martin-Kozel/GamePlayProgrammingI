# README #
This project is SFML FSM StarterKit, this works on Linux
For windows the includes, libraries and paths will need to be set manually
SFML is not supported on Cgwin or MSys2 on Windows so it requires a custom install.
  
## Installation Linux
* Download Repository to your Project Workspace
* Install **SFML** on **debian** based distro using `sudo apt-get install libsfml-dev`
* Navigate to root of project
* type `make`

## Installation Windows
* Download and install [MSYS64](https://www.msys2.org/)  
![MSYS64](./images/MsysWebsite.png)
* Open MSYS Bash
	* **STEP 1** of Updating msys `pacman -Syu` this will shutdown bash when complete.  
	![Pacman Update Step 1](./images/PacmanUpdateStep1.png)
	* **STEP 2** of Updating msys after this has complete restart MSYS Bash and run `pacman -Su`  
	![Pacman Update Step 2](./images/PacmanUpdateStep2.png)
	* **STEP 3** (Note this there are multiple commands below, to get toolchain up and running) Open MSYS Bash and install
>   * **STEP 3.1** **gcc** `pacman -S gcc`  
![Install GCC](./images/InstallGCC.png)
>   * **STEP 3.2** **mingw gcc** `pacman -S mingw-w64-x86_64-gcc`  
![Install MinGW GCC](./images/InstallMinGWGCC.png)
>   * **STEP 3.3** **mingw gdb** `pacman -S mingw-w64-x86_64-gdb`  
![Install GDB](./images/InstallMinGWGDB.png)
>   * **STEP 3.4** **make** `pacman -S make`  
![Install Make](./images/InstallMake.png)
>   * **STEP 3.5** **git** `pacman -S git`  
![Install Git](./images/InstallGit.png)
>   * **STEP 3.6** **SFML** `pacman -S mingw-w64-x86_64-sfml`see [MSYS Website Packages](https://packages.msys2.org/package/mingw-w64-x86_64-sfml).  
![Install SFML](./images/InstallSFML.png) 

* **STEP 4** Download GCC 7.3.0 MinGW (SEH) - 64-bit from [SFML Website](https://www.sfml-dev.org/download/sfml/2.5.1/) 
![GCC SFML](./images/DownloadSFMLGCC.png)
>  * Its good practice to place in `c:\devtools\SFML`  
![GCC SFML](./images/ExtractToDevtools.png)
>   * Before proceeding to next step ensure your directory structure looks like image below  
![GCC SFML](./images/DirectoryStructure.png)

* **STEP 5** Setup a Windows Environment Variable which points to where `GCC 7.3.0 MinGW (SEH) - 64-bit` is located, also set the location of DLLs in Windows Path.
![Set Environment Variable](./images/EnvironmentVariable.png)
![Set Environment Variable](./images/EnvironmentVariableBinPath.png)
>   * Restart MSYS64 Bash and check that enviroment variable exists by typing `echo {SFML_SDK}` in terminal. Also check that you can see includes, libs and DLLs  
![Verify Environment Variable](./images/Verify_SFML_SDK_Env_Variable.png)

* **STEP 6** Create a directory e.g. `Projects` for repository, then `cd c:/Projects' and Clone repository  
![Create Directory and Clone](./images/CloneRepo.png)

* **STEP 7** Ensure Windows SDK is installed, SFML depends on OpenGL libs. Windows SDK can be downloaded from [Microsoft Developer Website](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/) . Tested with version 19041.0.  
![Windows SDK](./images/Window10SDK.png)

* **STEP 8** Navigate to cloned project folder `sfml_game`
>   * Type `make` in MSYS Bash Terminal  
![Install GCC](./images/Make.png)

## What is this repository for? ##
* Getting started with Visual Studio Code, SFML, Makefiles and Finite State Machines on Linux and Windows (Note Makefile will work on both as long as toolchain is setup correctly)
* This is a great Tutorial to get this project running on [Windows](https://www.youtube.com/watch?v=Ljhpsdz8Ouo)

## Art Assets ##
* This starter kit contains numerous art assets including Walking, Jumping and attacks


## Who do I talk to? ##
* philip.bourke@itcarlow.ie