//
// Created by Huli on 11/30/2020.
//

#ifndef DISKSPEEDTEST_MULTITHREADLISTENER_H
#define DISKSPEEDTEST_MULTITHREADLISTENER_H

#include "InformationListener.h"

struct MultiThreadListener: public InformationListener {

private:

    int _is_locked = 0;

public:

    void add_wrote_size(const int &) override;

};


#endif //DISKSPEEDTEST_MULTITHREADLISTENER_H
