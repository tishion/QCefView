# CEF dependencies

This directory contains the CEF binaries and headers to use with QCefView.

You can get binary builds of CEF [from here](http://opensource.spotify.com/cefbuilds/index.html), and you'll then need to build `libcef_dll_wrapper` by following the instructions within the CEF download.

## Directory structure

The directory structure inside `dep/cef/` should look like the following:

- bin
    - Debug
    - Release
- include
- lib
    - Debug
    - Release
- resources

Where:

- The `bin` directories contain the CEF `.dll`s, `.bin`s, and `icudtl.dat`.
- The `lib` directories contain the CEF `.lib`s and your compiled `libcef_dll_wrapper.lib`.
- `include` and `resources` are directly copied from CEF.
