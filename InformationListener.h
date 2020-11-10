//
// Created by huli on 2020/11/10.
//

#ifndef DISKSPEEDTEST_INFORMATIONLISTENER_H
#define DISKSPEEDTEST_INFORMATIONLISTENER_H

struct InformationListener {

    double sample_sum = 0;

    int sample_count = 0;

    int thread_state = 0;

    double wrote_size = 0;

    int thread_signal = 0;

};

#endif //DISKSPEEDTEST_INFORMATIONLISTENER_H
