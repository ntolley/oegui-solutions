# Matlab Engine Processor Plugin
This plugin integrates open-ephys GUI with the Matlab Engine API (https://www.mathworks.com/help/matlab/calling-matlab-engine-from-c-programs-1.html?s_tid=CRUX_lftnav) 

The current implentation sends buffer data to 

## Configuring Plugin (Visual Studio 2017)
1) Edit file path in CMakeLists.txt with a path to a built version of plugin-GUI
```
set(ENV{GUI_BASE_DIR} C:/Users/tolle/Documents/GitHub/plugin-GUI)
````
2) Set the properties folder according to https://www.mathworks.com/matlabcentral/answers/100603-how-can-i-compile-a-matlab-engine-application-using-microsoft-visual-studio-9-0-or-10-0

2) In the Debugging panel of the properties folder, set "command" as \PathToFile\open-ephys.exe 

3) Edit file path in ProcessorPlugin.cpp constructor to your matlab script location
```
std::ifstream infile{ "C:\\your_matlab_script.txt" }; //reads .txt into string variable
````
4) Write matlab script. The buffer is loaded into the workspace as the variable 'X'. Any processing must be stored in 'X' without altering the original dimesions. 

