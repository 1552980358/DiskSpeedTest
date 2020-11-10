//
// Created by huli on 2020/11/10.
//

#include "sequence_write.h"
#include "InformationListener.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <random>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

using namespace std;

void sleep_in_millisecond(long millisecond) {
#ifdef WIN32
    Sleep(millisecond);
#elif _POSIX_C_SOURCE >= 199309L
    timespec ts;
    ts.tv_sec = millisecond / 1000;
    ts.tv_nsec = (millisecond % 1000) * 1000000;
    nanosleep(&ts, nullptr);
#else
    if (millisecond >= 1000)
      sleep(millisecond / 1000);
    usleep((millisecond % 1000) * 1000);
#endif
}

string cal_size(double current_size) {
    string tmp;
    if (current_size >= TB) {
        tmp = to_string(current_size / TB);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " TB";
    } else if (current_size >= GB) {
        tmp = to_string(current_size / 1E+9);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " GB";
    } else if (current_size >= MB) {
        tmp = to_string(current_size / 1E+6);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " MB";
    } else if (current_size >= KB) {
        tmp = to_string(current_size / 1E+3);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " KB";
    } else {
        tmp = to_string(current_size);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " B";
    }
}

void *sub_thread(void *listener) {

    auto *informationListener = (InformationListener *) listener;
    double current_size;
    double last_size;
    double different_in_size;
    long time_record;

    informationListener->thread_signal = 1;
    for (;!informationListener->thread_state;) {
        sleep_in_millisecond(1);
    }
    for (;informationListener->thread_state;) {
        current_size = informationListener->wrote_size;
        time_record = time_t(0);
        different_in_size = current_size - last_size;
        last_size = current_size;
        informationListener->sample_sum += different_in_size;
        informationListener->sample_count++;
        for (int i = 0; i < 15; ++i) {
            cout << "\b";
        }
        for (int i = 0; i < 15; ++i) {
            cout << ' ';
        }
        for (int i = 0; i < 15; ++i) {
            cout << "\b";
        }
        cout << cal_size(different_in_size) << "/s";
        sleep_in_millisecond(1000 - (time_t(0) - time_record));
    }

    pthread_exit(nullptr);
    return nullptr;
}

void sequence_write(string *target_path, int *no_of_set, int *no_of_gb) {

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