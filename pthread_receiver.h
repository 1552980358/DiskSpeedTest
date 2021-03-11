#pragma once

#ifndef DISKSPEEDTEST_PTHREAD_RECEIVER_H
#define DISKSPEEDTEST_PTHREAD_RECEIVER_H

#include <pthread.h>
#include <string>
using std::string;
#include "main_sender.h"
class main_sender;

class pthread_receiver {

private:

    int _current_proc = -1;

    pthread_t _pthread_id;

    main_sender *_sender = nullptr;

    pthread_receiver *_prev = nullptr;

    pthread_receiver *_next = nullptr;

    double _wrote = 0;

    string _path;

    double _byte_write;

public:

    pthread_receiver(main_sender *, pthread_receiver *, const string &, const double &);

    void wait_for();

    void write(double size);

    [[nodiscard]] double get_wrote() const;

    void set_next(pthread_receiver *);

    pthread_receiver *get_next();

    pthread_receiver *get_prev();

    pthread_t *get_pthread_id();

    void update_proc();

    [[nodiscard]] int get_proc() const;

    void set_path(const string &);

    string get_path();

    void set_byte_write(const double &);

    [[nodiscard]] double get_byte_write() const;

};


#endif //DISKSPEEDTEST_PTHREAD_RECEIVER_H
