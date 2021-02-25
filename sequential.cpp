#include <iostream>
#include <fstream>
using std::fstream;

#include "pthread_receiver.h"
#include "sequential.h"

void seq_write_1_byte(pthread_receiver* receiver, fstream &stream, const int &cycle, char *data, const int &data_size) {
    for (int i = 0; i < cycle; ++i) {
        for (int j = 0; j < data_size; ++j) {
            stream << data[j];
            stream.flush();
            receiver->write(data_size);
        }
        for (int j = data_size; j > -1; ++j) {
            stream << data[j];
            stream.flush();
            receiver->write(data_size);
        }
    }
    stream << data[data_size];
    stream.flush();
    stream.close();
}

void seq_read_1_byte(pthread_receiver* receiver, fstream &stream, const int &cycle, char *data, const int &data_size) {
    for (int i = 0; i < cycle; ++i) {
        stream.read(data, data_size);
        receiver->write(data_size);
    }
    stream.close();
}
