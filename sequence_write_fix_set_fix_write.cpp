//
// Created by huli on 2020/11/12.
//

#include "sequence_write_fix_set_fix_write.h"

void sequence_write_fix_set_fix_write(const int &type, const string &target_path, const int &no_of_gb) {

    cout << "Generate data..........";

    kByte_t data;
    switch (type) {
        case 0:
            for (auto &i: data) {
                i = 0;
            }
            break;
        case 1:
            for (auto &i: data) {
                i = 1;
            }
        case 2:
            for (auto &i: data) {
                // 10101010
                i = 252;
            }
            break;
        default:
            return;
    }

    cout << "Succeed" << endl
         << "Opening temporary test file..........";
    FILE *file = fopen(target_path.c_str(), "wb+");
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
        cout << i << "s";
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

    listener.thread_state = 1;
    for (i = 0; i < no_of_gb * MB; ++i) {
        fwrite(data, KB, 1, file);
        listener.wrote_size += KB;
    }
    fclose(file);

    cout << "..........Completed" << endl
         << "Remove temporary file.........." << (!remove(target_path.c_str()) ? "Succeed" : "Failed") << endl
         << endl
         << "========================================" << endl
         << "Write Size: " << no_of_gb << " GB" << endl
         << "Average: " << cal_size(listener.sample_sum / listener.sample_count) << "/s" << endl
         << "========================================" << endl
         << endl
         << endl;

}