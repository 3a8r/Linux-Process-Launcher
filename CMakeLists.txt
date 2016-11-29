cmake_minimum_required(VERSION 3.5)
project(ProcessLauncher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
FIND_PACKAGE ( Threads REQUIRED )
set(SOURCE_FILES main.cpp)
add_executable(ProcessLauncher ${SOURCE_FILES})
TARGET_LINK_LIBRARIES ( ProcessLauncher ${CMAKE_THREAD_LIBS_INIT} )
