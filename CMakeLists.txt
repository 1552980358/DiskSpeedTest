cmake_minimum_required(VERSION 3.17)
project(DiskSpeedTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

#include_directories(D:\\DiskSpeedTest\\WriteLibrary)
#link_directories(D:\\DiskSpeedTest\\WriteLibrary\\cmake-build-debug)

#include_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary)
#link_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary/cmake-build-debug)

#link_libraries(WriteLibrary)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(
        DiskSpeedTest
        main.cpp
        byte_size.h
        cal_size.cpp cal_size.h
        pthread_write_listener.h pthread_write_listener.cpp
        writing.h writing.cpp check_state.cpp check_state.h
        speed_sample.cpp speed_sample.h
)

#target_link_libraries(DiskSpeedTest WriteLibrary)