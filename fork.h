#pragma once

#include <string>
#include <semaphore.h>
#include <spdlog/spdlog.h>

using Logger = std::shared_ptr<spdlog::logger>;


class Fork{
    std::string forkName;
    std::string owner;
    sem_t *sem;
    Logger logger;

public:
    class FileObjectException{
    };

    explicit Fork(const std::string &name, const std::string &owner);
    ~Fork();

    void put();
    void take(std::time_t start_time);
    void logEating();
};
