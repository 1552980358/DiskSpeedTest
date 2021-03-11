#include "args_util.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
using std::getline;
#include <windows.h>
#include <ctime>
#include "cal_size.h"

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

bool is_numbers(const string& str) {
    for (char i : str) {
        if (i > '9' || i < '0') {
            return false;
        }
    }
    return true;
}

int configuration(string &file, double &no_of_byte, int &no_of_thread, bool *is_cpp) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    string input;
    cout << "Dir path to place test file: ";
    getline(cin, input);
    file = string(input);

    cout << "Num of GiB data to be writ[100]: ";
    getline(cin, input);
    if (!input.empty()) {
        if (!is_numbers(input)) {
            return false;
        }
        no_of_byte = (double) atoi(input.c_str()) * GB;
    }

    cout << "No of thread(s) use[" << info.dwNumberOfProcessors / 2 << "]: ";
    getline(cin, input);
    if (input.empty()) {
        no_of_thread = info.dwNumberOfProcessors / 2;
    } else {
        if (!is_numbers(input)) {
            return false;
        }
        no_of_thread = (int) atoi(input.c_str());
    }

    return true;
}

int argv_config(int argc, char **argv, string &file, double &no_of_byte, int &no_of_thread, bool *is_cpp) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
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
                    file = string(argv[i]);
                    break;
                }
                case 's': {
                    i++;
                    if (!argv[i]) {
                        cout << "No of GB not specified." << endl << "Usage: -s <NUM_OF_GB>." << endl;
                        return 0;
                    }
                    no_of_byte = get_argv_int(argv, i) * GB;
                    break;
                }
                case 'j': {
                    i++;
                    if (!argv[i]) {
                        cout << "No of thread not specified." << endl << "Usage: -j <NUM_OF_THREAD>." << endl;
                        return false;
                    }
                    no_of_thread = get_argv_int(argv, i);
                    break;
                }
                case 'N': {
                    i++;
                    auto tmp = string(argv[i]);
                    auto channel_speed = 250; // PCI-e Gen 1.0
                    if (tmp.size() == 3) {
                        if (tmp[1] != '.') {
                            cout << "PCI-e version and num of channels not specified" << endl
                                 << "Usage: -N <PCI-e_GENERATION>.<NUM_OF_CHANNELS>[.<MODE>]" << endl
                                 << "Example: -N 3.4.N";
                            return false;
                        }

                        switch (tmp[0]) {
                            case '1':
                                channel_speed *= 1;
                                break;
                            case '2':
                                channel_speed *= 2;
                                break;
                            case '3':
                                channel_speed *= 4;
                                break;
                            case '4':
                                channel_speed *= 8;
                                break;
                            case '5':
                                channel_speed *= 16;
                                break;
                            default:
                                cout << "Unknown value: \'" << tmp[0] << "\'." << endl
                                     << "PCI-e version and num of channels not specified" << endl
                                     << "Usage: -N <PCI-e_GENERATION>.<NUM_OF_CHANNELS>[.<MODE>]" << endl
                                     << "Example: -N 3.4.N";
                                return false;
                        }

                        if (tmp[2] < '0' || tmp[2] > '9') {
                            return false;
                        }

                        // Get the max speed
                        channel_speed *= (tmp[2] - 48);

                        // Configure according to channel speed
                        no_of_thread = channel_speed / 1024;
                        if (no_of_thread > info.dwNumberOfProcessors - 1) {
                            no_of_thread = (long) info.dwNumberOfProcessors - 1;
                        }

                        no_of_byte = channel_speed * 10;
                        break;
                    }

                    if (tmp.size() == 5) {
                        if (tmp[1] != '.' || tmp[3] != '.' || (tmp[4] != 'N' && tmp[4] != 'E')) {
                            cout << "PCI-e version and num of channels not specified" << endl
                                 << "Usage: -N <PCI-e_GENERATION>.<NUM_OF_CHANNELS>[.<MODE>]" << endl
                                 << "Example: -N 3.4.N" << endl;
                            return false;
                        }

                        switch (tmp[0]) {
                            case '1':
                                channel_speed *= 1;
                                break;
                            case '2':
                                channel_speed *= 2;
                                break;
                            case '3':
                                channel_speed *= 4;
                                break;
                            case '4':
                                channel_speed *= 8;
                                break;
                            case '5':
                                channel_speed *= 16;
                                break;
                            default:
                                cout << "Unknown value: \'" << tmp[0] << "\'." << endl
                                     << "PCI-e version and num of channels not specified" << endl
                                     << "Usage: -N <PCI-e_GENERATION>.<NUM_OF_CHANNELS>[.<MODE>]" << endl
                                     << "Example: -N 3.4.N" << endl;
                                return false;
                        }

                        if (tmp[4] == 'N') {
                            if (tmp[2] < '0' || tmp[2] > '9') {
                                return false;
                            }

                            // Get the max speed
                            channel_speed *= (tmp[2] - 48);

                            // Configure according to channel speed
                            no_of_thread = channel_speed / 1024;
                            if (no_of_thread > info.dwNumberOfProcessors - 1) {
                                no_of_thread = (long) info.dwNumberOfProcessors - 1;
                            }
                        } else {
                            no_of_thread = (long) info.dwNumberOfProcessors - 1;
                        }

                        no_of_byte = channel_speed * 10;
                        break;
                    }

                    cout << "PCI-e version and num of channels not specified" << endl
                         << "Usage: -N <PCI-e_GENERATION>.<NUM_OF_CHANNELS>[.<MODE>]" << endl
                         << "Example: -N 3.4.N";

                    break;
                }
                case 'c': {
                    auto str = string(argv[i]);
                    if (str == "-cpp") {
                        *is_cpp = true;
                        break;
                    }
                    if (str == "-c") {
                        *is_cpp = false;
                        break;
                    }
                    break;
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

