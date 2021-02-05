#include "pthread_write_listener.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::fstream;
using std::ios;

int pthread_write_listener::is_started = false;
byte_t *pthread_write_listener::data = nullptr;
string pthread_write_listener::dir;
int pthread_write_listener::size_write = 50 * MB;
bool pthread_write_listener::is_cpp = false;

pthread_write_listener::pthread_write_listener(pthread_write_listener *new_prev) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    if (new_prev) {
        set_prev(new_prev);
        new_prev->set_next(this);
    }
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

void pthread_write_listener::write_c_pp(const char *path) {

}

void pthread_write_listener::write_c_standard(const char *path) {
    FILE *file = fopen(path, "wb+");
    for (int i = 0; i < pthread_write_listener::size_write; i++) {
        try {
            fwrite(data, KB, 1, file);
        } catch (errno_t e) {
            cout << e << endl;
        }
        wrote += buffer;
    }
    fclose(file);
    delete file;
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