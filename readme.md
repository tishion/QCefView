Quick Start with Qt+Cef
======

checkout the repo and build the solution, you will get QCefView SDK, and then you can deploy it into your development environment.


How to change the CEF version
======

1. download cef binary distribution from https://cefbuilds.com 

2. build libcef_dll_wrapper.lib with your platform toolset, remember to use the same configuration of Runtime Library wiht the Qt SDK you are using (Project Properties > C/C++ > Code Generation > Runtime Library)

3. collect the cef binary files, lib files, inlucde files and resource files into the dep\cef\

4. build QCefView solution and you will get the QCefViewSDK
