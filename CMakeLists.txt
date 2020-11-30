cmake_minimum_required(VERSION 3.17)
project(DiskSpeedTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

#include_directories(D:\\DiskSpeedTest\\WriteLibrary)
#link_directories(D:\\DiskSpeedTest\\WriteLibrary\\cmake-build-debug)

#include_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary)
#link_directories(/cygdrive/d/DiskSpeedTest/WriteLibrary/cmake-build-debug)

#link_libraries(WriteLibrary)

add_executable(
        DiskSpeedTest
        main.cpp
        sequence_write_random_set_random_write.cpp sequence_write_random_set_random_write.h
        InformationListener.h InformationListener.cpp
        sequence_write_fix_set_fix_write.cpp sequence_write_fix_set_fix_write.h
        byte_size.h
        sub_thread.cpp sub_thread.h
        cal_size.cpp cal_size.h
        sleep_in_millisecond.cpp sleep_in_millisecond.h
        MultiThreadListener.cpp MultiThreadListener.h
        sequence_write_fix_set_fix_write.cpp sequence_write_fix_set_fix_write.h
)

#target_link_libraries(DiskSpeedTest WriteLibrary)