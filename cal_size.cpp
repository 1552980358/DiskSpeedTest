//
// Created by huli on 2020/11/12.
//

#include "cal_size.h"

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