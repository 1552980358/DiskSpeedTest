//
// Created by Huli on 2/2/2021.
//

#include "speed_sample.h"

speed_sample::speed_sample(double data, speed_sample *last) {
    _data = data;
    if (last) {
        _last = last;
        last->set_next(this);
    }
}

speed_sample *speed_sample::get_last() {
    return _last;
}

void speed_sample::set_next(speed_sample *next) {
    _next = next;
}

speed_sample *speed_sample::get_next() {
    return _next;
}

int speed_sample::get_data() const {
    return _data;
}