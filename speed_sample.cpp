#include "speed_sample.h"

speed_sample::speed_sample(double data, speed_sample *last) {
    _data = data;
    if (last) {
        _last = last;
        _last->set_next(this);
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

double speed_sample::get_data() const {
    return _data;
}