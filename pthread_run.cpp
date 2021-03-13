#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;
#include <chrono>
#include <fstream>
using std::fstream;
using std::ios;
auto &ios_bin = ios::binary;
auto &ios_in = ios::in;
auto &ios_out = ios::out;

#include "pthread_run.h"
#include "pthread_receiver.h"
#include "byte_size.h"
#include "sequential.h"
#include "random_access.h"

void *pthread_run(void *args) {
    auto *receiver = (pthread_receiver *) args;
    auto path = receiver->get_path();
    auto no_of_byte = receiver->get_byte_write();
    auto data = (char *) malloc(NUM_512 * sizeof(byte_t));

    default_random_engine e(time(nullptr));
    uniform_int_distribution<int> u(0, NUM_255);

    for (auto i = 0; i < NUM_512; ++i) {
        data[i] = u(e);
    }

    int cycle = no_of_byte / NUM_1024;

    fstream stream(path, ios_bin | ios_out);

    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, NUM_255);

    // 0
    receiver->update_proc();
    receiver->wait_for();
    seq_write_1_byte(receiver, stream, cycle, data, NUM_512);

    // 1
    receiver->update_proc();
    stream.open(path, ios_in | ios_bin);
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, NUM_255);

    // 2
    receiver->update_proc();
    receiver->wait_for();
    seq_read_1_byte(receiver, stream, cycle, data, NUM_512);

    // 3
    receiver->update_proc();
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, NUM_255);
    for (int i = 0; i < NUM_512; ++i) {
        data[i] = u(e);
    }
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, (int) (no_of_byte - sizeof(byte_t)));
    stream.open(path, ios_out | ios_bin);

    // 4
    receiver->update_proc();
    receiver->wait_for();
    ra_write_1_byte(receiver, stream, cycle, data, NUM_512, e, u);

    // 5
    receiver->update_proc();
    e = default_random_engine(time(nullptr));
    stream.open(path, ios_in | ios_bin);

    // 6
    receiver->update_proc();
    receiver->wait_for();
    ra_read_1_byte(receiver, stream, cycle, data, NUM_512, e, u);

    // 7
    receiver->update_proc();
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, NUM_255);
    data = (char *) realloc(data, NUM_4096);
    for (int i = 0; i < NUM_4096; ++i) {
        data[i] = u(e);
    }
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, (int) (no_of_byte - NUM_4096));
    stream.open(path, ios_out | ios_bin);

    // 8
    receiver->update_proc();
    receiver->wait_for();
    ra_write_4_k_byte(receiver, stream, cycle, data, NUM_4096, e, u);

    //9
    receiver->update_proc();
    e = default_random_engine(time(nullptr));
    stream.open(path, ios_in | ios_bin);

    // 10
    receiver->update_proc();
    receiver->wait_for();
    ra_read_4_k_byte(receiver, stream, cycle, data, NUM_4096, e, u);

    receiver->update_proc();
    free(data);

    return nullptr;
}