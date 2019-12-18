# Matlab Engine Processor Plugin
This plugin integrates open-ephys GUI with the Matlab Engine API (https://www.mathworks.com/help/matlab/calling-matlab-engine-from-c-programs-1.html?s_tid=CRUX_lftnav) 

The current implentation sends buffer data to 

## Configuring Plugin (Visual Studio 2017)
1) Edit file path in CMakeLists.txt with a path to a built version of plugin-GUI
```
set(ENV{GUI_BASE_DIR} /PathToFolder/plugin-GUI)
````
2) Create build files using CMake https://cmake.org/
	a) Set Source folder as \PathToFolder\matlab_filter
	b) Set Build folder as \PathToFolder\matlab_filter\Build
	c) Configure build files for Visual Studio 2017 and x64 

3) Set the properties folder according to https://www.mathworks.com/matlabcentral/answers/100603-how-can-i-compile-a-matlab-engine-application-using-microsoft-visual-studio-9-0-or-10-0

4) In the Debugging panel of the properties folder, set "command" as /PathToFile/open-ephys.exe

5) Edit file path in ProcessorPlugin.cpp constructor to your matlab script location
```
std::ifstream infile{ "C:\\your_matlab_script.txt" }; //reads .txt into string variable
````
6) Write matlab script. The buffer is loaded into the workspace as the variable 'X'. Any processing must be stored in 'X' without altering the original dimesions. 

