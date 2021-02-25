#include "pthread_receiver.h"

pthread_receiver::pthread_receiver(main_sender *sender, pthread_receiver *prev) {
    _sender = sender;
    if (prev) {
        _prev = prev;
        _prev->set_next(this);
    }
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