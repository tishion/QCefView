cmake_minimum_required(VERSION 3.4.1)
project(${QCEF_VIEW_DLL})

set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core GUI Widgets REQUIRED)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${QCEF_VIEW_SDK_LIB_OUT})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${QCEF_VIEW_SDK_LIB_OUT})

file(GLOB_RECURSE _SRC_FILES
  "*.cpp"
  "*.h"
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX Source FILES ${_SRC_FILES})

if (OS_WINDOWS)
  file(GLOB _RES_FILES
    "*.rc"
  )
  source_group(Resource ${_RES_FILES})
endif()

add_library(${PROJECT_NAME} SHARED 
  ${_SRC_FILES}
  ${_RES_FILES}
)

if (OS_WINDOWS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    QCEFVIEW_LIB
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt5::Core
	Qt5::Gui 
  Qt5::Widgets
  ${CEF_DLL_WRAPPER}
  ${CEF_LIB_FILE}
)

add_dependencies(${PROJECT_NAME} ${QCEF_WING_EXE})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEF_RESOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/icudtl.dat $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/icudtl.dat
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEF_BINARY_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Include ${QCEF_VIEW_SDK_INC_OUT}
)