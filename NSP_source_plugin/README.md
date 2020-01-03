# NSP Source
This plugin functions as a data thread to stream BlackRock Neural Signal Processor (NSP) data into open ephys. 

## Configuring Plugin (Visual Studio 2017)
1) Download and install Cerebus Central Suite (v 7.0.5.0) from https://www.blackrockmicro.com/technical-support/software-downloads/

2) Copy the following files from **'$\Blackrock'** and **'$\Blackrock\cbsdk\lib'** to the Debug directory of plugin-GUI (same folder as open-ephys.exe) 
	- cbsdkx64.dll
	- QtCorex644.dll
	- QtXmlx644.dll


3) Edit file path in CMakeLists.txt with a path to a built version of plugin-GUI
```
set(ENV{GUI_BASE_DIR} /PathToFolder/plugin-GUI)
````
2) Create build files using CMake https://cmake.org/
	- Set Source folder as **$\NSP_source_plugin\NSP_Source**
	- Set Build folder as **$\NSP_source_plugin\NSP_Source\Build**
	- Configure build files for Visual Studio 2017 and x64 

5) Open the solution file (.vxcproj) and make the following changes to the properties panel
	- (Configuration Properties -> Debugging) Set "command" as **'$\PathToFile\open-ephys.exe'**
	- (C/C++ -> General -> Additional Include Directories) Add **'$\Blackrock\cbsdk\include'**
	- (Linker -> General -> Additional Library Directories) Add **'$\Blackrock\cbsdk\lib'**
	- (Linker -> Input -> Additional Dependencies) Add **cbsdkx64.lib**
