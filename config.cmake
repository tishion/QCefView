#
# Build environment configuration file for QCefView
#

#
# The Qt SDK path
#
set(QT_SDK_DIR
  # Change this value to the Qt SDK path of your build environment
  "D:\\Qt\\5.12.4\\msvc2017_64\\"
)

#
# The root dir of the CEF SDK
#
set(CEF_SDK_DIR
  # Change this value to the CEF binary distribution path of your build environment
  "${CMAKE_CURRENT_SOURCE_DIR}/dep/cef_binary_76.1.13+gf19c584+chromium-76.0.3809.132_windows64"
)

#################################################################################
#
# For CI system
#
if (DEFINED ENV{APPVEYOR})
  set(QT_SDK_DIR
    # Change this value to the Qt SDK path of your build environment
    "C:\\Qt\\5.12.4\\msvc2017_64"
  )
endif()