#include <iostream>
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
    auto *receiver = (pthread_receiver *) ((void **)args)[0];
    auto *path = (const char *) ((void **)args)[1];
    auto *no_of_byte = (double *) ((void **)args)[2];

    auto data = (char *) malloc(NUM_512 * sizeof(byte_t));
    default_random_engine e(time(nullptr));
    uniform_int_distribution<int> u(0, NUM_255);
    for (auto i = 0; i < NUM_512; ++i) {
        data[i] = u(e);
    }

    int cycle = *no_of_byte / NUM_1024;

    fstream stream(path, ios_bin | ios_out);

    // 0
    receiver->update_proc();

    receiver->wait_for();
    seq_write_1_byte(receiver, stream, cycle, data, sizeof(byte_t));

    // 1
    receiver->update_proc();
    stream.open(path, ios_in | ios_bin);
    cycle /= 2;

    // 2
    receiver->update_proc();
    receiver->wait_for();
    seq_read_1_byte(receiver, stream, cycle, data, sizeof(byte_t));

    // 3
    receiver->update_proc();
    stream.open(path, ios_out | ios_in | ios_bin);
    cycle *= 2;
    e = default_random_engine(time(nullptr));
    u = uniform_int_distribution(0, NUM_255);
    for (int i = 0; i < NUM_512; ++i) {
        data[i] = u(e);
    }
    u = uniform_int_distribution(0, (int) (*no_of_byte - sizeof(byte_t)));

    // 4
    receiver->update_proc();
    receiver->wait_for();
    ra_write_1_byte(receiver, stream, cycle, data, sizeof(byte_t), e, u);

    receiver->update_proc();
    receiver->wait_for();

    //


    receiver->update_proc();
    receiver->wait_for();

    //

    receiver->update_proc();
    receiver->wait_for();

    //

    receiver->update_proc();
    receiver->wait_for();

    //

    receiver->update_proc();
    receiver->wait_for();

    //



    return nullptr;
}