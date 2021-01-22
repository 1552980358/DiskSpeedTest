#include "pthread_write_listener.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::fstream;
using std::ios;
#include "cal_size.h"

int pthread_write_listener::is_started = false;
kByte_t pthread_write_listener::data = "";
string pthread_write_listener::dir;
int pthread_write_listener::size_write = 50 * MB;

pthread_write_listener::pthread_write_listener(pthread_write_listener *new_prev) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    set_prev(new_prev);
}

void pthread_write_listener::set_prev(pthread_write_listener *new_prev) {
    pthread_write_listener::prev = new_prev;
}

void pthread_write_listener::set_next(pthread_write_listener *new_next) {
    pthread_write_listener::next = new_next;
}

pthread_write_listener *pthread_write_listener::get_prev() {
    return prev;
}

pthread_write_listener *pthread_write_listener::get_next() {
    return next;
}

pthread_t *pthread_write_listener::getPThreadID() {
    return &pthread;
}

pthread_t *pthread_write_listener::get_launched() {
    status_launch = !status_launch;
    return getPThreadID();
}

int pthread_write_listener::is_launched() const {
    return status_launch;
}

void pthread_write_listener::write(FILE *file) {
    for (int i = 0; i < pthread_write_listener::size_write; i++) {
        try {
            fwrite(data, KB, 1, file);
        } catch (errno_t e) {
            cout << e << endl;
        }
        wrote += buffer;
    }
    fclose(file);
    complete();
}

double pthread_write_listener::wrote_size() const {
    return wrote;
}

int pthread_write_listener::is_completed() const {
    return is_complete;
}

void pthread_write_listener::complete() {
    is_complete = true;
}