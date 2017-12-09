#pragma once

#include <string>
#include <semaphore.h>
#include <fstream>
#include <spdlog/logger.h>
#include <time.h>


class Fork{
    std::string forkName;
    std::string owner;
    sem_t *sem;
    std::ofstream resource;

public:
    class FileObjectException{
    };

    explicit Fork(const std::string &name, const std::string &owner);
    ~Fork();

    void put();
    void take(std::time_t start_time);
    void logEating();

private:
    void log(std::string message);
    std::string getCurrentTime();
};
