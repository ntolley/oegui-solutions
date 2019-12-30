# NSP Source
This plugin functions as a data thread to stream BlackRock Neural Signal Processor (NSP) data into open ephys. 

## Configuring Plugin (Visual Studio 2017)
1) Download and install Cerebus Central Suite (v 7.0.5.0) from https://www.blackrockmicro.com/technical-support/software-downloads/

2) Copy the following files to Debug directory of plugin-GUI (same folder as open-ephys.exe) 
'$\Blackrock'
	- cbsdk.dll
	- cbsdk.lib
	- QtCore4.dll
	- QtCorex644.lib
	- QtXml4.dll
	- QtXmlx644.dll

 '$Blackrock\cbsdk\lib' 
	- cbsdkx64.dll
	- cbsdkx64.lib

3) Edit file path in CMakeLists.txt with a path to a built version of plugin-GUI
```
set(ENV{GUI_BASE_DIR} /PathToFolder/plugin-GUI)
````
4) Create build files using CMake https://cmake.org/
	a) Set Source folder as $\PathToFolder\matlab_filter
	b) Set Build folder as $\PathToFolder\matlab_filter\Build
	c) Configure build files for Visual Studio 2017 and x64 

5) Open the solution file (.vxcproj) and make the following changes to the properties panel
	a) (Configuration Properties -> Debugging) Set "command" as '$\PathToFile\open-ephys.exe'
	b) (C/C++ -> General -> Additional Include Directories) Add '$\Blackrock\cbsdk\include'
	c) (Linker -> General -> Additional Library Directories) Add '$\Blackrock\cbsdk\lib'
	d) (Linker -> Input -> Additional Dependencies) Add cbsdkx64.lib
