#include <iostream>
#include <string>
#include "sequence_write.h"
using namespace std;

int main() {

    string path = "E:\\test";
    int set = 50;
    int gb = 5;
    sequence_write(&path, &set, &gb);

    return 0;
}
