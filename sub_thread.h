//
// Created by huli on 2020/11/12.
//

#ifndef DISKSPEEDTEST_SUB_THREAD_H
#define DISKSPEEDTEST_SUB_THREAD_H

#include <iostream>
#include <pthread.h>
#include "InformationListener.h"
#include "MultiThreadListener.h"
#include "cal_size.h"
#include "sleep_in_millisecond.h"
using namespace std;

void *sub_thread(void *);

#endif //DISKSPEEDTEST_SUB_THREAD_H
