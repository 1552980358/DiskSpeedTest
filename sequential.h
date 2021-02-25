#ifndef DISKSPEEDTEST_SEQUENTIAL_H
#define DISKSPEEDTEST_SEQUENTIAL_H

void seq_write_1_byte(pthread_receiver *, fstream &, const int &, char *, const int &);

void seq_read_1_byte(pthread_receiver*, fstream &, const int &, char *, const int &);

#endif //DISKSPEEDTEST_SEQUENTIAL_H
