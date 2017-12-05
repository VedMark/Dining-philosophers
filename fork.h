#pragma once

#include <string>
#include <semaphore.h>
#include <spdlog/logger.h>

struct  shared_data_t
{
    pthread_mutex_t mutex;
    long refCount;
};

using Logger = std::shared_ptr<spdlog::logger>;


class Fork{
    std::string forkName;
    std::string shmName;
    std::string owner;
    sem_t *sem;
    shared_data_t *sharedData;
    Logger logger;

public:
    class FileObjectException{
    };

    explicit Fork(const std::string &name, const std::string &owner, const Logger &logger);
    ~Fork();

    void post();
    void wait(std::time_t start_time);

private:
    void mapSharedMemoryToProcessVirtualAddressSpace(int shm);
    void initSharedMemory();
};
