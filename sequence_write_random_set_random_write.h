//
// Created by huli on 2020/11/10.
//

#ifndef DISKSPEEDTEST_SEQUENCE_WRITE_RANDOM_SET_RANDOM_WRITE_H
#define DISKSPEEDTEST_SEQUENCE_WRITE_RANDOM_SET_RANDOM_WRITE_H

#include <string>
#include "InformationListener.h"
#include <iostream>
#include <pthread.h>
#include <random>
#include <ctime>
using namespace std;
using std::string;
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <ctime>
#else
#include <unistd.h>
#endif
#include "byte_size.h"
#include "cal_size.h"

void sleep_in_millisecond(long);

void *sub_thread(void *);

void sequence_write_random_set_random_write(string *, int *, int *);

#endif //DISKSPEEDTEST_SEQUENCE_WRITE_RANDOM_SET_RANDOM_WRITE_H
