#ifndef DISKSPEEDTEST_ARGS_UTIL_H
#define DISKSPEEDTEST_ARGS_UTIL_H

#include <string>
using std::string;

int get_config(int, char **, string &, double &, int &, bool &);

int get_argv_int(char **argv, int i);

#endif //DISKSPEEDTEST_ARGS_UTIL_H
