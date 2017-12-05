#pragma once

#include <string>
#include <semaphore.h>
#include <spdlog/logger.h>

using Logger = std::shared_ptr<spdlog::logger>;


class Fork{
    std::string forkName;
    std::string shmName;
    std::string owner;
    sem_t *sem;
    Logger logger;

public:
    class FileObjectException{
    };

    explicit Fork(const std::string &name, const std::string &owner, const Logger &logger);
    ~Fork();

    void post();
    void wait(std::time_t start_time);
};
