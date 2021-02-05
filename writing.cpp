#include "writing.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
using std::fstream;
using std::ios;
#include "pthread_write_listener.h"

void wait_for_start() {
    while (!pthread_write_listener::is_started);
}

void write(pthread_write_listener *listener, const char *path, bool is_cpp) {
    wait_for_start();
    is_cpp ? listener->write_c_pp(path) : listener->write_c_standard(path);
}

void *fun_write(void *argv) {
    auto listener = (pthread_write_listener *) argv;

    string path = pthread_write_listener::dir + '/' + to_string(*listener->getPThreadID());

    cout << "Thread #" + to_string((int) *listener->get_launched()) + ": Launched!\n";
    // wait_for_start();

    // fstream stream(pthread_write_listener::dir + '/' + to_string(*listener->getPThreadID()), ios::out | ios::binary);
    // listener->write_c_standard(&stream);
    write(listener, path.c_str(), pthread_write_listener::is_cpp);

    return nullptr;
}