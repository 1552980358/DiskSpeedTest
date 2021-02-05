//
// Created by Huli on 2/2/2021.
//

#include "sample_analysis.h"
#include "speed_sample.h"

int get_max_speed(speed_sample *head) {
    speed_sample *current = head;
    int max = 0;
    while (current) {
        if (current->get_data() > max) {
            max = current->get_data();
        }
        current = current->get_next();
    }
    return max;
}

int get_min_speed(speed_sample *head) {
    speed_sample *current = head;
    int min = head->get_data();
    while (current) {
        if (current->get_data() < min) {
            min = current->get_data();
        }
        current = current->get_next();
    }
    return min;
}

speed_sample *remove_samples(speed_sample *head) {
    speed_sample *current = head;
    while (current->get_next()) {
        current = current->get_next();
    }
    speed_sample *selected;
    while (current->get_last()) {
        selected = current;
        current = current->get_last();
        delete selected;
    }
    delete current;
    return nullptr;
}