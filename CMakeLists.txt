cmake_minimum_required(VERSION 3.17)
project(DiskSpeedTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

#include_directories(D:\\DiskSpeedTest\\WriteLibrary)
#link_directories(D:\\DiskSpeedTest\\WriteLibrary\\cmake-build-debug)

#include_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary)
#link_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary/cmake-build-debug)

#link_libraries(WriteLibrary)

add_executable(DiskSpeedTest main.cpp sequence_write.cpp sequence_write.h InformationListener.h)

#target_link_libraries(DiskSpeedTest WriteLibrary)