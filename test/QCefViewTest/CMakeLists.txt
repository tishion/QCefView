cmake_minimum_required(VERSION 3.4.1)
project(QCefViewTest)

set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core GUI Widgets REQUIRED)

include_directories(
  ${CMAKE_BINARY_DIR}/out/${QCEF_VIEW_DLL}
)

file(GLOB_RECURSE _SRC_FILES
  "*.h"
  "*.cpp"
)

file(GLOB_RECURSE _UI_FILES
  "*.ui"
)
source_group("Form Files" ${_UI_FILES})

if (OS_WINDOWS)
  file(GLOB_RECURSE _RES_FILES
    "*.qrc"
    "*.rc"
  )
  source_group("Resource Files" ${_RES_FILES})
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${PROJECT_NAME})

add_executable(${PROJECT_NAME} WIN32 
  ${_SRC_FILES}
  ${_UI_FILES}
  ${_RES_FILES}
)

if (OS_WINDOWS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
  )
  set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Test)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt5::Core
	Qt5::Gui 
  Qt5::Widgets
  ${QCEF_VIEW_DLL}
)

# Embed the manifest file into the target
if (MSVC)
  if (CMAKE_MAJOR_VERSION LESS 3)
		message(WARNING "CMake version 3.0 or newer is required use build variable TARGET_FILE")
	else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND mt.exe -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\${PROJECT_NAME}.manifest\" -inputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\" -outputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\"
    )
  endif()
endif(MSVC)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/QCefViewTestPage.html $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${QCEF_VIEW_SDK_BIN_OUT}/$<CONFIGURATION> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)