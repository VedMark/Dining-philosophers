#include <iostream>
#include "philosopher.h"

const char *SEM_NAME("/fork");
const int PROC_COUNT = 5;

std::string getForkName(int proc_id);

int main(int argc, char *argv[]) {
    if (argc != 3)
        return 1;

    std::string fork_names[2];
    int proc_id = std::stoi(argv[1]);

    if (proc_id == 4) {
        fork_names[0] = getForkName(proc_id + 1);
        fork_names[1] = getForkName(proc_id);
    }
    else {
        fork_names[0] = getForkName(proc_id);
        fork_names[1] = getForkName(proc_id + 1);
    }

    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S:%e] [%l] %v");

    try {
        Philosopher philosopher(argv[2], fork_names[0], fork_names[1], spdlog::stdout_logger_st("logger"));
        philosopher.exist();
    }
    catch (Fork::FileObjectException) {
        std::cerr << "Errors received while processing file objects" << std::endl;
    }

    return 0;
}

std::string getForkName(int proc_id) {
    return SEM_NAME + std::__cxx11::to_string(proc_id % PROC_COUNT);
}
