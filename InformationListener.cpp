//
// Created by Huli on 11/30/2020.
//

#include "InformationListener.h"

void InformationListener::add_sample_value(const double &value) {
    _sample_sum += value;
    _sample_count++;
}

double InformationListener::get_sample_average() const {
    return _sample_sum / _sample_count;
}

void InformationListener::add_wrote_size(const int &value) {
    _wrote_size += value;
}

double InformationListener::get_wrote_size() const {
    return _wrote_size;
}