//
// Created by huli on 2020/11/12.
//

#ifndef DISKSPEEDTEST_SLEEP_IN_MILLISECOND_H
#define DISKSPEEDTEST_SLEEP_IN_MILLISECOND_H

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

void sleep_in_millisecond(long);

#endif //DISKSPEEDTEST_SLEEP_IN_MILLISECOND_H
