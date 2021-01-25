//
// Created by Huli on 1/25/2021.
//

#include "check_state.h"

int check_is_launched(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    while (listener) {
        if (!listener->is_launched()) {
            return false;
        }
        listener = listener->get_next();
    }
    return true;
}

int are_all_completed(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    while (listener) {
        if (!listener->is_completed()) {
            return false;
        }
        listener = listener->get_next();
    }
    return true;
}

double get_sum(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    double sum = 0;
    while (listener) {
        sum += listener->wrote_size();
        listener = listener->get_next();
    }
    return sum;
}