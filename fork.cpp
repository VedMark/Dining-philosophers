#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "fork.h"

#define SEMAPHORE_NAME(fork) ("/" + (fork))

Fork::Fork(const std::string &_name, const std::string &_owner) :
        forkName(_name), owner(_owner) {

    if (SEM_FAILED == (sem = sem_open(SEMAPHORE_NAME(forkName).c_str(), O_CREAT, 0777, 1))) {
        logger->error(strerror(errno));
        throw FileObjectException();
    }
    logger = spdlog::rotating_logger_st(forkName +"_logger", "logs/" + forkName, 1024 * 1024 * 16, 0);
}

Fork::~Fork() {
    sem_unlink(SEMAPHORE_NAME(forkName).c_str());
}

void Fork::put() {
    logger->info(owner + " put " + forkName);
    sem_post(sem);
}

void Fork::take(std::time_t start_time) {
    sem_wait(sem);
    auto end_time = std::time(nullptr);
    logger->info(owner + " took " + forkName + " after " + std::to_string(end_time - start_time) + "s of waiting");
}

void Fork::logEating() {
    logger->info(owner + " started eating");
}

