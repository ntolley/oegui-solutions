# Matlab Engine Processor Plugin
This plugin integrates open-ephys GUI with the Matlab Engine API (https://www.mathworks.com/help/matlab/calling-matlab-engine-from-c-programs-1.html?s_tid=CRUX_lftnav) 

The current implentation sends buffer data to 

## Configuring Plugin (Visual Studio 2017)
1) Set the properies folder according to https://www.mathworks.com/matlabcentral/answers/100603-how-can-i-compile-a-matlab-engine-application-using-microsoft-visual-studio-9-0-or-10-0

2) Edit file path in ProcessorPlugin.cpp constructor 
```
std::ifstream infile{ "C:\\your_matlab_script.txt" }; //reads .txt into string variable
````
3) Write matlab script. The buffer is loaded into the workspace as the variable 'X'. Any processing must be stored in 'X' without altering the original dimesions. 

