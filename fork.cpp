#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "fork.h"

Fork::Fork(const std::string &_name, const std::string &_owner, const Logger &_logger) :
        forkName(_name), shmName(_name + "_shm"), owner(_owner), logger(_logger) {

    if (SEM_FAILED == (sem = sem_open(forkName.c_str(), O_CREAT, 0777, 1))) {
        logger->error(strerror(errno));
        throw FileObjectException();
    }
}

Fork::~Fork() {
    sem_unlink(forkName.c_str());
}

void Fork::post() {
    sem_post(sem);
    logger->info(owner + " put " + forkName);
}

void Fork::wait(std::time_t start_time) {
    sem_wait(sem);
    auto end_time = std::time(nullptr);
    logger->info(owner + " got " + forkName + " after " + std::to_string(end_time - start_time) + "s of waiting");
}
