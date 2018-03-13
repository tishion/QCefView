Quick Start with Qt+Cef https://tishion.github.io/QCefView 
======

Checkout the repo and follow the build instructions below. You will get the QCefView SDK, and then you can deploy it into your development environment.

Building
------

1. Download the CEF binary distribution from:
    - http://opensource.spotify.com/cefbuilds/index.html

2. Build `libcef_dll_wrapper.lib` with your platform toolset, remember to use the same configuration of Runtime Library wiht the Qt SDK you are using (Project Properties > C/C++ > Code Generation > Runtime Library)

3. Collect the CEF binary files, lib files, inlucde files and resource files into `dep\cef\` (following the instructions in the README there)

4. Build QCefView solution and you will get the QCefViewSDK
