//
// Created by huli on 2020/11/12.
//

#include "sleep_in_millisecond.h"

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