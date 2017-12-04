#include <iostream>
#include "philosopher.h"

const char *SEM_NAME("/fork");
const int PROC_COUNT = 5;

std::string getForkName(int proc_id);

int main(int argc, char *argv[]) {
    if(argc != 3)
        return 1;

    std::string fork_names[2];
    int proc_id = std::stoi(argv[1]);

    fork_names[0] = getForkName(proc_id + proc_id % 2 ? 0 : 1);
    fork_names[1] = getForkName(proc_id + proc_id % 2 ? 1 : 0);

    Philosopher philosopher(argv[2], fork_names[0], fork_names[1]);
    philosopher.exist();

    return 0;
}

std::string getForkName(int proc_id) {
    return SEM_NAME + std::__cxx11::to_string(proc_id % PROC_COUNT);
}
