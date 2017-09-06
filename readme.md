Quick Start with Qt+Cef
======

checkout the repo and build the solution, you will get QCefView SDK, and then you can deploy it into your development environment.


How to change the CEF version
======

1. download cef binary distribution from ~~~https://cefbuilds.com~~~  http://opensource.spotify.com/cefbuilds/index.html

2. build libcef_dll_wrapper.lib with your platform toolset, remember to use the same configuration of Runtime Library wiht the Qt SDK you are using (Project Properties > C/C++ > Code Generation > Runtime Library)

3. collect the cef binary files, lib files, inlucde files and resource files into the dep\cef\

4. build QCefView solution and you will get the QCefViewSDK


Some frequent questions on building this project
======

I need to say, I don't provide binary distribution of this projects becasue there are so many different version CEF and Qt, I can not guarantee one binary copy will meet many developers requirement. You must know this project is just a code level framework to demonstrate how to integrate Qt and CEF, how to design and implement a mechanism to support the communication between Javascript and C++ code. 

Then how to choose the build tools and version:

**No matter what version VS you want to use you have to build the libcef_dll_wrapper(in CEF) with the VS you chosen.**

Let's say:
If 
  I want to use Qt 5.7 and VS 2015
then
  1. you need to download Qt 5.7 SDK for VS 2015 and install it
  2. you need to build the libcef_dll_warpper with VS 2015
  you can do 2 first and then 1, the order donesn't matter.
