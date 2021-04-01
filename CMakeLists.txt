# 
# The main config file for QCefView
# NOTE:
#   Usually there is no need to change this file.
#   Change the config.cmake instead.
#
cmake_minimum_required(VERSION 3.18)
project(QCefView)

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(OS_MACOSX 1)
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(OS_LINUX 1)
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(OS_WINDOWS 1)
endif()

# Determine the project architecture.
if(NOT DEFINED PROJECT_ARCH)
  if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PROJECT_ARCH "x86_64")
  else()
    set(PROJECT_ARCH "x86")
  endif()

  if(OS_MACOSX)
    # PROJECT_ARCH should be specified on Mac OS X.
    message(WARNING "No PROJECT_ARCH value specified, using ${PROJECT_ARCH}")
  endif()
endif()

# Set common configurations
###############################################################
# Use solution folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(QCEF_VIEW_SDK_OUT ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME})
set(QCEF_VIEW_SDK_BIN_OUT ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME}/bin)
set(QCEF_VIEW_SDK_LIB_OUT ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME}/lib)
set(QCEF_VIEW_SDK_INC_OUT ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${QCEF_VIEW_SDK_BIN_OUT})
###############################################################

# Include the local config files
###############################################################
include(config.cmake)
###############################################################

# Append the QT dir to CMAKE_PREFIX_PATH
###############################################################
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_SDK_DIR})
###############################################################


# Set CEF root dir and append it to CMAKE_MODULE_PATH
###############################################################
set(CEF_ROOT "${CEF_SDK_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
###############################################################


# Config the CEF
###############################################################
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)

# Set the runtime library type
set(CEF_RUNTIME_LIBRARY_FLAG "/MD" CACHE STRING "Use dynamic runtime")

# Disable the SANDBOX
set(USE_SANDBOX OFF CACHE BOOL "Disable the Sandbox")

# Disable the ATL
set(USE_ATL OFF CACHE STRING "Disable the ATL")

# Find the CEF package
find_package(CEF REQUIRED)

# Store the libcef.lib path and cef dll wrapper target name
# NOTE: we set this just for simplify the following referring.
set(CEF_LIB_FILE "${CEF_BINARY_DIR}/libcef.lib")
set(CEF_DLL_WRAPPER "libcef_dll_wrapper")

# Add build target 
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH})
PRINT_CEF_CONFIG()
###############################################################


# Add all targets
###############################################################
add_subdirectory(src/QCefProto)

include_directories(
  src/QCefProto
  ${CEF_ROOT}
)

set(QCEF_WING_EXE "QCefWing")
add_subdirectory(src/QCefWing)

set(QCEF_VIEW_DLL "QCefView")
add_subdirectory(src/QCefView)
###############################################################


# Config the Demo project
###############################################################
if ((NOT DEFINED SKIP_BUILD_DEMO) OR (SKIP_BUILD_DEMO STREQUAL "") OR (${SKIP_BUILD_DEMO} MATCHES "(FALSE|false|0|OFF)"))
    option(SKIP_BUILD_DEMO "Skip building of demo" OFF)
    message(STATUS "FLAG SKIP_BUILD_DEMO is OFF")
elseif(${SKIP_BUILD_DEMO} MATCHES "(TRUE|true|1|ON)")
    option(SKIP_BUILD_DEMO "Skip building of demo" ON)
    message(STATUS "FLAG SKIP_BUILD_DEMO is ON")
else()
    message(FATAL_ERROR "++++++++++ INVALID FLAG SKIP_BUILD_DEMO=" ${SKIP_BUILD_DEMO})
endif()

if (NOT SKIP_BUILD_DEMO)
  add_subdirectory(test/QCefViewTest)
endif()
###############################################################
