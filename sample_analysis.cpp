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
    int min = 0;
    while (current) {
        if (current->get_data() < min) {
            min = current->get_data();
        }
        current = current->get_next();
    }
    return min;
}