#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <pthread.h>
#include <windows.h>
#include "cal_size.h"
#include "pthread_write_listener.h"
#include "writing.h"

int get_config(int, char **, string &, int &, int &);
int get_argv_int(char **, int);
pthread_write_listener *create_threads(int);

void wait_for_thread_launched(pthread_write_listener *);
int check_is_launched(pthread_write_listener *);

void show_speed(pthread_write_listener *);
int are_all_completed(pthread_write_listener *);
double get_sum(pthread_write_listener *);

int main(int argc, char **argv) {
    string file;
    auto no_of_gb = 10 * MB;
    auto no_of_thread = 1;

    if (!get_config(argc, argv, file, no_of_gb, no_of_thread)) {
        return 1;
    }

    pthread_write_listener::dir = file;
    pthread_write_listener::size_write = no_of_gb;

    for (auto &i : pthread_write_listener::data) {
        i = 127;
    }

    cout << "Directory: " << file << endl
         << "Num of GB to write: " << no_of_gb << endl
         << "Num of threads: " << no_of_thread << endl;

    pthread_write_listener *head = create_threads(no_of_thread);
    wait_for_thread_launched(head);
    pthread_write_listener::is_started = true;

    show_speed(head);

    return 0;
}

int get_config(int argc, char **argv, string &file, int &no_of_gb, int &no_of_thread) {
    auto i = 1;
    while (i < argc) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'D':
                case 'd': {
                    i++;
                    if (argv[i][0] == '-') {
                        cout << "Parameter usage: -d <PATH>." << endl;
                        return 0;
                    }
                    for (char c_str: string(argv[i])) {
                        file += c_str;
                    }
                    break;
                }
                case 'S':
                case 's': {
                    i++;
                    if (!argv[i]) {
                        cout << "No of GB not specified." << endl << "Usage: -S <NUM_OF_GB> or -s <NUM_OF_GB>." << endl;
                        return 0;
                    }
                    no_of_gb = get_argv_int(argv, i);
                    break;
                }
                case 'j': {
                    i++;
                    if (!argv[i]) {
                        cout << "No of GB not specified." << endl << "Usage: -j <NUM_OF_THREAD>." << endl;
                    }
                    no_of_thread = get_argv_int(argv, i);
                }
            }
        } else {
            cout << "Unknown argument '\'" << argv[i] << "\' ." << endl;
            return 0;
        }

        i++;
    }
    return 1;
}

int get_argv_int(char **argv, int i) {
    auto j = 0;
    auto k = 0;
    while (true) {
        try {
            if (!argv[i][j] || argv[i][j] == '\0' || argv[i][j] < '0' || argv[i][j] > '9') {
                break;
            }
            k = k * 10 + argv[i][j] - 48;
        } catch (errno_t) { return 0; }
        j++;
    }
    return k;
}

pthread_write_listener *create_threads(int no_of_thread) {
    pthread_write_listener *last = nullptr;
    pthread_write_listener *listener;
    // Using concept of linked list
    for (auto i = 0; i < no_of_thread; ++i) {
        listener = new pthread_write_listener(last);
        if (last) {
            last->set_next(listener);
        }
        last = listener;
        pthread_create(listener->getPThreadID(), nullptr, fun_write, (void *) listener);
    }
    while (listener->get_prev()) {
        listener = listener->get_prev();
    }
    return listener;
}

void wait_for_thread_launched(pthread_write_listener *head) {
    while (!check_is_launched(head)) {}
}

int check_is_launched(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    while (listener) {
        if (!listener->is_launched()) {
            return false;
        }
        listener = listener->get_next();
    }
    return true;
}

void show_speed(pthread_write_listener *head) {
    double last_sum = 0;
    double current_sum;
    string text;
    while (!are_all_completed(head)) {
        current_sum = get_sum(head);
        for (int i = 0; i < text.size(); ++i) {
            cout << '\b';
        }
        for (int i = 0; i < text.size(); ++i) {
            cout << ' ';
        }
        for (int i = 0; i < text.size(); ++i) {
            cout << '\b';
        }
        cout << (text = cal_size(current_sum) + " wrote, " + cal_size_miB(current_sum - last_sum) + "/s");
        last_sum = current_sum;
        Sleep(1000);
    }
}

int are_all_completed(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    while (listener) {
        if (!listener->is_completed()) {
            return false;
        }
        listener = listener->get_next();
    }
    return true;
}

double get_sum(pthread_write_listener *head) {
    pthread_write_listener *listener = head;
    double sum = 0;
    while (listener) {
        sum += listener->wrote_size();
        listener = listener->get_next();
    }
    return sum;
}