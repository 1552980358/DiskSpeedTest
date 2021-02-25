#ifndef DISKSPEEDTEST_SAMPLE_SUMMARY_H
#define DISKSPEEDTEST_SAMPLE_SUMMARY_H


#include "speed_sample.h"

class sample_summary {

private:

    double _avg = 0;

    double _max = 0;

    double _min = 0;

    double _cache = -1;

public:

    void cal_avg(speed_sample *);

    void find_max(speed_sample *);

    void find_min(speed_sample *);

    void find_cache(speed_sample *);

    [[nodiscard]] double get_avg() const;

    [[nodiscard]] double get_max() const;

    [[nodiscard]] double get_min() const;

    [[nodiscard]] double get_cache() const;

};


#endif //DISKSPEEDTEST_SAMPLE_SUMMARY_H
