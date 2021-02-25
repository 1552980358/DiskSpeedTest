cmake_minimum_required(VERSION 3.17)
project(DiskSpeedTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(
        DiskSpeedTest
        main.cpp
        byte_size.h
        cal_size.cpp cal_size.h
        speed_sample.cpp speed_sample.h
        sequential.cpp sequential.h
        random_access.cpp random_access.h
        pthread_receiver.cpp pthread_receiver.h
        main_sender.cpp main_sender.h
        pthread_run.cpp pthread_run.h
        sample_summary.cpp sample_summary.h
        args_util.cpp args_util.h
)

#target_link_libraries(DiskSpeedTest WriteLibrary)