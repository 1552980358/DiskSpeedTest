#include "main_sender.h"

main_sender::main_sender() = default;

void main_sender::start() {
    _current_proc++;
}

int main_sender::get_current_proc() const {
    return _current_proc;
}

void main_sender::set_pthread_receiver(pthread_receiver *head) {
    _pthread_receiver_head = head;
}

pthread_receiver *main_sender::get_pthread_receiver_head() {
    return _pthread_receiver_head;
}

bool is_not_online(pthread_receiver *head, const int &proc) {
    auto *ptr = head;
    while (head) {
        if (head->get_proc() != proc) {
            return true;
        }
        ptr = ptr->get_next();
    }
    return false;
}

void main_sender::wait_for_online() {
    while (is_not_online(_pthread_receiver_head, _current_proc));
}