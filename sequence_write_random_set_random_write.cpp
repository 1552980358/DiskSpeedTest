//
// Created by huli on 2020/11/10.
//

#include "sequence_write_random_set_random_write.h"

void sequence_write_random_set_random_write(string *target_path, int *no_of_set, int *no_of_gb) {

    cout << "Generate random data..........";
    default_random_engine defaultRandomEngine;
    uniform_int_distribution uniformIntDistribution(0, 128);
    unsigned char random_data[*no_of_set][KB];
    for (auto &i: random_data) {
        for (unsigned char &j: i) {
            j = uniformIntDistribution(defaultRandomEngine);
        }
    }
    cout << "Succeed" << endl
        << "Opening temporary test file..........";

    FILE *file = fopen(target_path->c_str(), "wb+");
    if (file == nullptr) {
        cout << "Failed" << endl;
        return;
    }
    cout << "Succeed" << endl
        << "Launching thread..........";

    InformationListener listener;
    pthread_t pthread;
    pthread_create(&pthread, nullptr, sub_thread, (void *) &listener);
    int i;
    for (i = 1; i <= 10 && !listener.thread_signal; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << '\b';
        }
        cout << i<< "s";
        sleep_in_millisecond(1000);
    }

    for (int j = 0; j < (i >= 10 ? 3 : 2); ++j) {
        cout << '\b';
    }
    if (!listener.thread_signal) {
        cout << "Failed" << endl;
        return;
    }
    cout << "Succeed" << endl
        << "Test launch:" << endl;

    defaultRandomEngine = default_random_engine();
    uniformIntDistribution = uniform_int_distribution(0, *no_of_set);
    listener.thread_state = 1;
    for (i = 0; i < *no_of_gb * MB; ++i) {
        fwrite(random_data[uniformIntDistribution(defaultRandomEngine)], KB, 1, file);
        listener.wrote_size += KB;
    }

    fclose(file);
    listener.thread_state = 0;
    cout << "..........Completed" << endl
        << "Remove temporary file.........." << (!remove(target_path->c_str()) ? "Succeed" : "Failed") << endl
        << endl
        << "========================================" << endl
        << "Write Size: " << *no_of_gb << " GB" << endl
        << "Average: " << cal_size(listener.sample_sum / listener.sample_count) << "/s" << endl
        << "========================================" << endl
        << endl
        << endl;

#if WIN32 || WIN64
    system("pause");
#else
    cout << "Press any key to continue...";
    getchar();
#endif
}