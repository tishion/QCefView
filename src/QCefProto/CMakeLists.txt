cmake_minimum_required(VERSION 3.4.1)
project(QCefProto)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)

add_library(${PROJECT_NAME}
  QCefProtocol.h
  QCefProtocol.cpp
)