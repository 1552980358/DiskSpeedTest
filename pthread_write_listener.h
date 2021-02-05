#ifndef DISKSPEEDTEST_PTHREAD_WRITE_LISTENER_H
#define DISKSPEEDTEST_PTHREAD_WRITE_LISTENER_H
#include <string>
using std::string;
#include <pthread.h>
#include <fstream>
using std::fstream;
#include "byte_size.h"

class pthread_write_listener {

private:
    pthread_write_listener *prev = nullptr;
    pthread_write_listener *next = nullptr;
    pthread_t pthread;
    int status_launch = false;
    double wrote = 0;
    int is_complete = false;

public:
    explicit pthread_write_listener(pthread_write_listener *);

    // 1KiB
    static byte_t *data;
    static int is_started;
    static string dir;
    static bool is_cpp;

    const static int buffer = 1024;
    static int size_write;

    void set_prev(pthread_write_listener *);
    void set_next(pthread_write_listener *);

    pthread_write_listener *get_prev();
    pthread_write_listener *get_next();

    pthread_t *getPThreadID();

    pthread_t *get_launched();
    [[nodiscard]] int is_launched() const;

    void write_c_standard(const char *);
    void write_c_pp(const char *);

    [[nodiscard]] double wrote_size() const;

    [[nodiscard]] int is_completed() const;
    void complete();

};


#endif //DISKSPEEDTEST_PTHREAD_WRITE_LISTENER_H
