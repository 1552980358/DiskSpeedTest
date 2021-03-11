#include "pthread_receiver.h"

pthread_receiver::pthread_receiver(main_sender *sender, pthread_receiver *prev, const string &path, const double &byte_write) {
    _sender = sender;
    if (prev) {
        _prev = prev;
        _prev->set_next(this);
    }
    set_path(path);
    set_byte_write(byte_write);
}

void pthread_receiver::wait_for() {
    while (_sender->get_current_proc() != _current_proc);
}

void pthread_receiver::write(double size) {
    _wrote += size;
}

double pthread_receiver::get_wrote() const {
    return _wrote;
}

void pthread_receiver::set_next(pthread_receiver *next) {
    _next = next;
}

pthread_receiver *pthread_receiver::get_next() {
    return _next;
}

pthread_receiver *pthread_receiver::get_prev() {
    return _prev;
}

pthread_t *pthread_receiver::get_pthread_id() {
    return &_pthread_id;
}

void pthread_receiver::update_proc() {
    _current_proc++;
}

int pthread_receiver::get_proc() const {
    return _current_proc;
}

void pthread_receiver::set_path(const string &path) {
    _path = path;
}

string pthread_receiver::get_path() {
    return _path;
}

void pthread_receiver::set_byte_write(const double &byte_write) {
    _byte_write = byte_write;
}

double pthread_receiver::get_byte_write() const {
    return _byte_write;
}