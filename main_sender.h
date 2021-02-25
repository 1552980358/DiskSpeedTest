#pragma once

#ifndef DISKSPEEDTEST_MAIN_SENDER_H
#define DISKSPEEDTEST_MAIN_SENDER_H

#include "pthread_receiver.h"
class pthread_receiver;

class main_sender {

private:
    int _current_proc = -1;

    pthread_receiver *_pthread_receiver_head = nullptr;

public:
    main_sender();

    [[nodiscard]] int get_current_proc() const;

    void start();

    void set_pthread_receiver(pthread_receiver *);

    pthread_receiver *get_pthread_receiver_head();

    void wait_for_online();

};


#endif //DISKSPEEDTEST_MAIN_SENDER_H
