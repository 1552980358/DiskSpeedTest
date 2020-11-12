//
// Created by huli on 2020/11/12.
//

#include "sub_thread.h"

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

void sleep_in_millisecond(long millisecond) {
#ifdef WIN32
    Sleep(millisecond);
#elif _POSIX_C_SOURCE >= 199309L
    timespec ts;
    ts.tv_sec = millisecond / 1000;
    ts.tv_nsec = (millisecond % 1000) * 1000000;
    nanosleep(&ts, nullptr);
#else
    if (millisecond >= 1000)
      sleep(millisecond / 1000);
    usleep((millisecond % 1000) * 1000);
#endif
}

void *sub_thread(void *listener) {

    auto *informationListener = (InformationListener *) listener;
    double current_size;
    double last_size;
    double different_in_size;
    long time_record;

    informationListener->thread_signal = 1;
    for (;!informationListener->thread_state;) {
        sleep_in_millisecond(1);
    }
    for (;informationListener->thread_state;) {
        current_size = informationListener->wrote_size;
        time_record = time_t(0);
        different_in_size = current_size - last_size;
        last_size = current_size;
        informationListener->sample_sum += different_in_size;
        informationListener->sample_count++;
        for (int i = 0; i < 15; ++i) {
            cout << "\b";
        }
        for (int i = 0; i < 15; ++i) {
            cout << ' ';
        }
        for (int i = 0; i < 15; ++i) {
            cout << "\b";
        }
        cout << cal_size(different_in_size) << "/s";
        sleep_in_millisecond(1000 - (time_t(0) - time_record));
    }

    pthread_exit(nullptr);
    return nullptr;
}