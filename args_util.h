#ifndef DISKSPEEDTEST_ARGS_UTIL_H
#define DISKSPEEDTEST_ARGS_UTIL_H
#include <string>
using std::string;

int configuration(string &file, double &no_of_byte, int &no_of_thread, bool *is_cpp);

int argv_config(int argc, char **argv, string &file, double &no_of_byte, int &no_of_thread, bool *is_cpp);

#endif //DISKSPEEDTEST_ARGS_UTIL_H
