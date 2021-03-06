#include <iostream>
#include <fstream>
using std::fstream;
#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include "random_access.h"
#include "pthread_receiver.h"

void ra_write_1_byte(pthread_receiver *receiver, fstream &stream, const int &cycle, const char *data, const int &data_size, default_random_engine &e, uniform_int_distribution<int> &u) {
    for (int i = 0; i < cycle; ++i) {
        stream.seekp(u(e));
        for (int j = 0; j < data_size; ++j) {
            stream << data[j];
        }
        for (int j = data_size - 1; j > -1; --j) {
            stream << data[j];
        }
        stream.flush();
        receiver->write(data_size * 2);
    }
    stream.close();
}

void ra_read_1_byte(pthread_receiver *receiver, fstream &stream, const int &cycle, char *data, const int &data_size, default_random_engine &e, uniform_int_distribution<int> &u) {
    for (int i = 0; i < cycle; ++i) {
        stream.seekp(u(e));
        stream.read(data, data_size);
        receiver->write(data_size);
    }
    stream.close();
}

void ra_write_4_k_byte(pthread_receiver *receiver, fstream &stream, const int &cycle, char *data, const int &data_size, default_random_engine &e, uniform_int_distribution<int> &u) {
    for (int i = 0; i < cycle; ++i) {
        stream.seekp(u(e));
        stream.write(data, data_size);
        stream.flush();
        receiver->write(data_size);
    }
    stream.close();
}

void ra_read_4_k_byte(pthread_receiver *receiver, fstream &stream, const int &cycle, char *data, const int &data_size, default_random_engine &e, uniform_int_distribution<int> &u) {
    for (int i = 0; i < cycle; ++i) {
        stream.seekp(u(e));
        stream.read(data, data_size);
        receiver->write(data_size);
    }
    stream.close();
}