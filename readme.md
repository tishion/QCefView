Quick Start with Qt+Cef https://tishion.github.io/QCefView 
======

This is the fresh new reforming version of QCefView, if you need to use the legacy one please checkout the ***legacy-archive*** branch.


Build instruction:

1. Download and install [CMake](https://cmake.org/)

2. Download and install Qt SDK from [Qt Downloads](https://download.qt.io/archive/qt/)

3. Download CEF binary distribution [Chromium Embedded Framework (CEF) Automated Builds](http://opensource.spotify.com/cefbuilds/index.html) and extract it to ***dep*** directory, for example:
    ```
    root
    ├─dep
    │  └─cef_binary_76.1.13+gf19c584+chromium-76.0.3809.132_windows64
    ├─src
    └─test
    ```

4. Modify the [config.cmake](config.cmake) to set the required build configurations

5. Just use CMake to build the project, for example:
    ``` bat
    REM create the build folder 
    mkdir build.win && cd build.win

    REM generate and build the project
    cmake .. && cmake --build .
    ```

> Note:
When I start the reforming I use Qt 5.12.4 and CEF cef_binary_76.1.13+gf19c584+chromium-76.0.3809.132_windows64. You need to make sure the version you are choosing is compatible with the code in this repo.