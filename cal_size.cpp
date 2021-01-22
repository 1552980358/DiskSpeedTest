//
// Created by huli on 2020/11/12.
//

#include "cal_size.h"
#include <string>
using std::to_string;

string cal_size(double current_size) {
    string tmp;
    if (current_size >= TB) {
        tmp = to_string(current_size / TB);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " TiB";
    } else if (current_size >= GB) {
        tmp = to_string(current_size / 1E+9);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " GiB";
    } else if (current_size >= MB) {
        tmp = to_string(current_size / 1E+6);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " MiB";
    } else if (current_size >= KB) {
        tmp = to_string(current_size / 1E+3);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " KiB";
    } else {
        tmp = to_string(current_size);
        tmp = tmp.substr(0, tmp.find('.'));
        return tmp + " B";
    }
}

string cal_size_miB(double current_size) {
    return to_string(current_size / MB) + "MiB";
}