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

int InformationListener::is_thread_ready() {
    return thread_signal;
}

void InformationListener::thread_ready() {
    thread_signal = 1;
}

void InformationListener::start_writing() {
    thread_state = 1;
}

int InformationListener::is_started_writing() {
    return thread_state;
}

void InformationListener::complete_writing() {
    thread_state = 0;
}

void InformationListener::add_wrote_size(const int &value) {
    _wrote_size += value;
}

double InformationListener::get_wrote_size() const {
    return _wrote_size;
}