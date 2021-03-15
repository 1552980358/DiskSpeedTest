#include <iostream>
using std::cout;
using std::endl;
using std::ios;
using std::ofstream;
using std::flush;

#include <string>
using std::string;
using std::to_string;

#include <pthread.h>
#include <malloc.h>
#include <windows.h>
#include <cstdio>

#include "cal_size.h"
#include "speed_sample.h"
#include "pthread_receiver.h"
#include "main_sender.h"
#include "pthread_run.h"
#include "args_util.h"
#include "sample_summary.h"

pthread_receiver *create_thread(main_sender *, const string &, const double &, const int &, bool *);

sample_summary *get_sample_summary(main_sender *, pthread_receiver *);

void recycle_samples(speed_sample *);

int main(int argc, char **argv) {

    string file;
    auto no_of_byte = 100 * (double) GB;
    auto no_of_thread = 2;
    auto *is_cpp = new bool(true);

    if (argc == 1) {
        if (!configuration(file, no_of_byte, no_of_thread, is_cpp)) {
            return 1;
        }
    } else if (!argv_config(argc, argv, file, no_of_byte, no_of_thread, is_cpp)) {
        return 1;
    }

    cout << "======================" << endl
         << "Dir: " << file << endl
         << "Num of thread: " << no_of_thread << endl
         << "Num of bytes: " << cal_size(no_of_byte) << endl
         << "======================" << endl
         << "Press any key to start...";
    getchar();

    auto *sender = new main_sender();

    // Create thread
    sender->set_pthread_receiver(create_thread(sender, file, no_of_byte, no_of_thread, is_cpp));
    pthread_receiver *receiver = sender->get_pthread_receiver_head();

    cout << "Waiting for threads..." << endl;
    // 0
    sender->wait_for_online();
    cout << "General Sequential Write" << endl;
    // 1
    sender->update_proc();
    auto *seq_write_byte_summary = get_sample_summary(sender, receiver);

    // 2
    sender->update_proc();
    cout << "Waiting for threads..." << endl;
    sender->wait_for_online();
    cout << "General Sequential Read" << endl;
    // 3
    sender->update_proc();
    auto *seq_read_byte_summary = get_sample_summary(sender, receiver);

    // 4
    sender->update_proc();
    cout << "Waiting for threads..." << endl;
    sender->wait_for_online();
    cout << "General Random Access Write" << endl;
    // 5
    sender->update_proc();
    auto *ra_write_byte_summary = get_sample_summary(sender, receiver);

    // 6
    sender->update_proc();
    cout << "Waiting for threads..." << endl;
    sender->wait_for_online();
    cout << "General Random Access Read" << endl;
    // 7
    sender->update_proc();
    auto *ra_read_byte_summary = get_sample_summary(sender, receiver);

    // 8
    sender->update_proc();
    cout << "Waiting for threads..." << endl;
    sender->wait_for_online();
    cout << "Random Access 4K Write" << endl;
    // 9
    sender->update_proc();
    auto *ra_write_4_k_byte_summary = get_sample_summary(sender, receiver);

    // 10
    sender->update_proc();
    cout << "Waiting for threads..." << endl;
    sender->wait_for_online();
    cout << "Random Access 4K Read" << endl;
    // 11
    sender->update_proc();
    auto *ra_read_4_k_byte_summary = get_sample_summary(sender, receiver);

    cout << "====================" << endl << endl;

    cout << "General Sequential Write" << endl
         << "Max: " << cal_size_miB(seq_write_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(seq_write_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(seq_write_byte_summary->get_avg()) << "/s" << endl
         << endl;

    cout << "General Sequential Read" << endl
         << "Max: " << cal_size_miB(seq_read_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(seq_read_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(seq_read_byte_summary->get_avg()) << "/s" << endl
         << endl;

    cout << "General Random Access Write" << endl
         << "Max: " << cal_size_miB(ra_write_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(ra_write_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(ra_write_byte_summary->get_avg()) << "/s" << endl
         << endl;

    cout << "General Random Access Read" << endl
         << "Max: " << cal_size_miB(ra_read_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(ra_read_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(ra_read_byte_summary->get_avg()) << "/s" << endl
         << endl;

    cout << "Random Access 4K Write" << endl
         << "Max: " << cal_size_miB(ra_write_4_k_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(ra_write_4_k_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(ra_write_4_k_byte_summary->get_avg()) << "/s" << endl
         << endl;

    cout << "Random Access 4K Read" << endl
         << "Max: " << cal_size_miB(ra_read_4_k_byte_summary->get_max()) << "/s" << endl
         << "Min: " << cal_size_miB(ra_read_4_k_byte_summary->get_min()) << "/s" << endl
         << "Avg: " << cal_size_miB(ra_read_4_k_byte_summary->get_avg()) << "/s" << endl
         << endl;

    getchar();
    return 0;
}

pthread_receiver *
create_thread(main_sender *sender, const string &file, const double &no_of_byte, const int &no_of_thread,
              bool *is_cpp) {
    pthread_receiver *receiver = nullptr;
    for (int i = 0; i < no_of_thread; ++i) {
        receiver = new pthread_receiver(sender, receiver, file + "/" + to_string(i), no_of_byte / no_of_thread);
        pthread_create(receiver->get_pthread_id(), nullptr, pthread_run, (void *) receiver);
    }
    while (receiver->get_prev()) {
        receiver = receiver->get_prev();
    }
    return receiver;
}

bool are_all_continue(main_sender *sender, pthread_receiver *receiver) {
    pthread_receiver *ptr = receiver;
    while (ptr) {
        if (ptr->get_proc() == sender->get_current_proc()) {
            return true;
        }
        ptr = ptr->get_next();
    }
    return false;
}

double get_wrote_sum(pthread_receiver *receiver) {
    double sum = 0;
    auto *ptr = receiver;
    while (ptr) {
        sum += ptr->get_wrote();
        ptr = ptr->get_next();
    }
    return sum;
}

speed_sample *get_samples(main_sender *sender, pthread_receiver *receiver) {
    speed_sample *sample = nullptr;
    while (are_all_continue(sender, receiver)) {
        Sleep(1000);
        sample = new speed_sample(get_wrote_sum(receiver), sample);
        cout << "\r" + cal_size_miB(sample->get_data() - (sample->get_last() ? sample->get_last()->get_data() : 0)) + "/s     ";
        cout.flush();
    }
    cout << "Handling with data..." << endl;
    while (sample->get_last()) {
        sample = sample->get_last();
    }
    return sample;
}

sample_summary *get_sample_summary(main_sender *sender, pthread_receiver *receiver) {
    auto *sample = get_samples(sender, receiver);
    auto *summary = new sample_summary();
    summary->cal_avg(sample);
    summary->find_max(sample);
    summary->find_min(sample);
    summary->find_cache(sample);
    recycle_samples(sample);
    return summary;
}

void recycle_samples(speed_sample *head) {
    speed_sample *next;
    speed_sample *current = head;
    while (current) {
        next = current->get_next();
        delete current;
        current = next;
    }
}
