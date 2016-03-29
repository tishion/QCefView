1. download cef binary distribution from https://cefbuilds.com 

2. build libcef_dll_wrapper.lib with your platform toolset, remember to use the [Multi-thread DLL(/MD)] & [Multi-thread DLL Debug (/MDd)] Runtime Library

3. put the cef binary files, lib files, inlucde files and resource files into the dep\cef\ folder

4. install and configure Qt development environment

5. build QCefView solution and you will get the QCefViewSDK
