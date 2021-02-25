#pragma once

#ifndef DISKSPEEDTEST_PTHREAD_RECEIVER_H
#define DISKSPEEDTEST_PTHREAD_RECEIVER_H

#include <pthread.h>

#include "main_sender.h"
class main_sender;

class pthread_receiver {

private:

    int _current_proc = -1;

    pthread_t _pthread_id{};

    main_sender *_sender = nullptr;

    pthread_receiver *_prev = nullptr;

    pthread_receiver *_next = nullptr;

    double _wrote = 0;

public:

    pthread_receiver(main_sender *, pthread_receiver *);

    void wait_for();

    void write(double size);

    double get_wrote() const;

    void set_next(pthread_receiver *);

    pthread_receiver *get_next();

    pthread_receiver *get_prev();

    pthread_t *get_pthread_id();

    void update_proc();

    [[nodiscard]] int get_proc() const;

};


#endif //DISKSPEEDTEST_PTHREAD_RECEIVER_H
