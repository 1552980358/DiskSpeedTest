//
// Created by huli on 2020/11/10.
//

#ifndef DISKSPEEDTEST_INFORMATIONLISTENER_H
#define DISKSPEEDTEST_INFORMATIONLISTENER_H
#include "byte_size.h"

struct InformationListener {

private:

    double _wrote_size = 0;

    double _sample_sum = 0;

    int _sample_count = 0;

    int thread_state = 0;

    int thread_signal = 0;

public:

    void add_sample_value(const double &);

    double get_sample_average() const;

    virtual int is_thread_ready();

    virtual void thread_ready();

    virtual void start_writing();

    virtual int is_started_writing();

    virtual void complete_writing();

    virtual void add_wrote_size(const int &);

    double get_wrote_size() const;

};

#endif //DISKSPEEDTEST_INFORMATIONLISTENER_H
