//
// Created by huli on 2020/11/10.
//

#ifndef DISKSPEEDTEST_INFORMATIONLISTENER_H
#define DISKSPEEDTEST_INFORMATIONLISTENER_H

struct InformationListener {

private:

    double _wrote_size = 0;

    double _sample_sum = 0;

    int _sample_count = 0;

public:

    void add_sample_value(const double &);

    double get_sample_average() const;

    int thread_state = 0;

    int thread_signal = 0;

    virtual void add_wrote_size(const int &);

    double get_wrote_size() const;

};

#endif //DISKSPEEDTEST_INFORMATIONLISTENER_H
