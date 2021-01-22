#include "writing.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
#include <fstream>
using std::fstream;
using std::ios;
#include "pthread_write_listener.h"

void wait_for_start() {
    while (!pthread_write_listener::is_started) {}
}

void *fun_write(void *argv) {
    auto listener = (pthread_write_listener *) argv;

    cout << "Thread #" << listener->get_launched() << ": Launched!" << endl;
    wait_for_start();

    // fstream stream(pthread_write_listener::dir + '/' + to_string(*listener->getPThreadID()), ios::out | ios::binary);
    // listener->write(&stream);
    FILE *file = fopen((pthread_write_listener::dir + '/' + to_string(*listener->getPThreadID())).c_str(), "wb+");
    listener->write(file);

    return nullptr;
}