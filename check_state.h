//
// Created by Huli on 1/25/2021.
//

#ifndef DISKSPEEDTEST_CHECK_STATE_H
#define DISKSPEEDTEST_CHECK_STATE_H

#include "pthread_write_listener.h"

int check_is_launched(pthread_write_listener *);

int are_all_completed(pthread_write_listener *);

double get_sum(pthread_write_listener *);

#endif //DISKSPEEDTEST_CHECK_STATE_H
