#include <iostream>
#include "philosopher.h"

const char *SEM_NAME("/fork");
const int PROC_COUNT = 5;

std::string getForkName(int proc_id);

int main(int argc, char *argv[]) {
    if(argc != 3)
        return 1;

    std::string fork_names[2];
    fork_names[0] = getForkName(std::stoi(argv[1]));
    fork_names[1] = getForkName(std::stoi(argv[1]) + 1);

    Fork lFork(fork_names[0]);
    Fork rFork(fork_names[1]);

    Philosopher philosopher(std::stoul(argv[1]), argv[2], lFork, rFork);
    philosopher.exist();

    return 0;
}

std::string getForkName(int proc_id) {
    return SEM_NAME + std::__cxx11::to_string(proc_id % PROC_COUNT);
}
