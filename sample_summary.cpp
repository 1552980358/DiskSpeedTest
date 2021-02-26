#include "sample_summary.h"

void sample_summary::cal_avg(speed_sample *head) {
    speed_sample *ptr = head;
    _avg = 0;
    int i = 0;
    while (ptr) {
        _avg += ptr->get_data();
        i++;
        ptr = ptr->get_next();
    }
    _avg /= i;
}

void sample_summary::find_max(speed_sample *head) {
    speed_sample *ptr = head;
    _max = head->get_data();
    while (ptr) {
        if (_max > head->get_data()) {
            _max = head->get_data();
        }
        ptr = ptr->get_next();
    }
}

void sample_summary::find_min(speed_sample *head) {
    speed_sample *ptr = head;
    _min = head->get_data();
    while (ptr) {
        if (_min < head->get_data()) {
            _min = head->get_data();
        }
        ptr = ptr->get_next();
    }
}

void sample_summary::find_cache(speed_sample *head) {
    speed_sample *ptr = head;
    auto last_speed = head->get_data();
    double current_speed;
    while (ptr) {
        if (ptr->get_next()) {
            if (((current_speed = head->get_next()->get_data() - head->get_data()) - last_speed) / last_speed < -0.4) {
                _cache = head->get_data();
                break;
            }
            last_speed = current_speed;
        }
        ptr = ptr->get_next();
    }
}

double sample_summary::get_avg() const {
    return _avg;
}

double sample_summary::get_max() const {
    return _max;
}

double sample_summary::get_min() const {
    return _min;
}

double sample_summary::get_cache() const {
    return _cache;
}