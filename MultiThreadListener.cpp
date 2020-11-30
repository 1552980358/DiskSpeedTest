//
// Created by Huli on 11/30/2020.
//

#include "MultiThreadListener.h"

void MultiThreadListener::add_wrote_size(const int &value) {
    for (; _is_locked;) {}
    _is_locked = !_is_locked;
    InformationListener::add_wrote_size(value);
    _is_locked = !_is_locked;
}