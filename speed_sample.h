//
// Created by Huli on 2/2/2021.
//

#ifndef DISKSPEEDTEST_SPEED_SAMPLE_H
#define DISKSPEEDTEST_SPEED_SAMPLE_H


struct speed_sample {

private:
    int _data;
    speed_sample *_last = nullptr;
    speed_sample *_next = nullptr;

public:
    speed_sample(int, speed_sample *);

    speed_sample *get_last();

    void set_next(speed_sample *);
    speed_sample *get_next();

    int get_data() const;

};


#endif //DISKSPEEDTEST_SPEED_SAMPLE_H
