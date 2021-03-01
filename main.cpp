#include <iostream>
using std::cout;
using std::endl;
using std::ios;
using std::ofstream;
#include <string>
using std::string;
using std::to_string;
#include <pthread.h>
#include <malloc.h>
#include <windows.h>

#include "cal_size.h"
#include "speed_sample.h"
#include "pthread_receiver.h"
#include "main_sender.h"
#include "pthread_run.h"
#include "args_util.h"
#include "sample_summary.h"

pthread_receiver *create_thread(main_sender *, const string &, const double &, const int &, const bool &);
sample_summary *get_sample_summary(main_sender *,pthread_receiver *);
void recycle_samples(speed_sample *);

int main(int argc, char **argv) {

    string file;
    double no_of_byte = 10.0 * GB;
    auto no_of_thread = 2;
    bool is_cpp = true;

    if (!get_config(argc, argv, file, no_of_byte, no_of_thread, is_cpp)) {
        return 1;
    }

    auto *sender = new main_sender();

    // Create thread
    sender->set_pthread_receiver(create_thread(sender, file, no_of_byte, no_of_thread, is_cpp));
    pthread_receiver *receiver = sender->get_pthread_receiver_head();

    // -1
    sender->wait_for_online();
    // 0
    sender->update_proc();
    auto *seq_write_byte_summary = get_sample_summary(sender, receiver);

    // 1
    sender->update_proc();
    sender->wait_for_online();
    // 2
    sender->update_proc();
    auto *seq_read_byte_summary = get_sample_summary(sender, receiver);

    // 3
    sender->update_proc();
    sender->wait_for_online();
    // 4
    sender->update_proc();
    auto *ra_write_byte_summary = get_sample_summary(sender, receiver);

    // 5
    sender->update_proc();
    sender->wait_for_online();
    // 6
    sender->update_proc();
    auto *ra_read_byte_summary = get_sample_summary(sender, receiver);

    // 7
    sender->update_proc();
    sender->wait_for_online();
    // 8
    sender->update_proc();
    auto *ra_write_4_k_byte_summary = get_sample_summary(sender, receiver);

    // 9
    sender->update_proc();
    sender->wait_for_online();
    // 10
    sender->update_proc();
    auto *ra_read_4_k_byte_summary = get_sample_summary(sender, receiver);

    cout << "====================" << endl << endl;
    getchar();
    return 0;
}

pthread_receiver *create_thread(main_sender *sender, const string &file, const double &no_of_byte, const int &no_of_thread, const bool &is_cpp) {
    pthread_receiver *receiver = nullptr;
    string path;
    for (int i = 0; i < no_of_thread; ++i) {
        receiver = new pthread_receiver(sender, receiver);
        path = (file + "\\" + to_string(i));
        void *args[] = {(void *) sender, (void *) path.c_str(), (void *) &no_of_byte};
        pthread_create(receiver->get_pthread_id(), nullptr, pthread_run, args);
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
        cout << sample->get_data() - sample->get_last()->get_data() << " B/s" << endl;
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
