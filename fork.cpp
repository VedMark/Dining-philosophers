#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ios>

#include "fork.h"

#define SEMAPHORE_NAME(fork) ("/" + (fork))

Fork::Fork(const std::string &_name, const std::string &_owner) :
        forkName(_name), owner(_owner) {

    if (SEM_FAILED == (sem = sem_open(SEMAPHORE_NAME(forkName).c_str(), O_CREAT, 0777, 1))) {
        log(strerror(errno));
        throw FileObjectException();
    }
}

Fork::~Fork() {
    sem_unlink(SEMAPHORE_NAME(forkName).c_str());
}

void Fork::put() {
    log(owner + " put " + forkName);
    sem_post(sem);
}

void Fork::take(std::time_t start_time) {
    sem_wait(sem);
    auto end_time = std::time(nullptr);
    auto message = owner + " took " + forkName + " after " + std::to_string(end_time - start_time) + "s of waiting";
    log(message);
}

void Fork::log(std::string message) {
    resource.open("logs/" + forkName + ".log", std::fstream::app);
    resource << "[" << getCurrentTime() << "] " << message << std::endl;
    resource.close();
}

void Fork::logEating() {
    log(owner + " started eating");
}

std::string Fork::getCurrentTime() {
    auto time = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(time);
    auto str = std::string(std::ctime(&t));
    return str.substr(0, str.length() - 1);
}

