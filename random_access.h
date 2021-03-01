#ifndef DISKSPEEDTEST_RANDOM_ACCESS_H
#define DISKSPEEDTEST_RANDOM_ACCESS_H

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include "pthread_receiver.h"

void ra_write_1_byte(pthread_receiver *, fstream &, const int &, const char *, const int &, default_random_engine &, uniform_int_distribution<int> &);

void ra_read_1_byte(pthread_receiver *, fstream &, const int &, char *, const int &, default_random_engine &, uniform_int_distribution<int> &);

void ra_write_4_k_byte(pthread_receiver *, fstream &, const int &, char *, const int &, default_random_engine &, uniform_int_distribution<int> &);

void ra_read_4_k_byte();

#endif //DISKSPEEDTEST_RANDOM_ACCESS_H
