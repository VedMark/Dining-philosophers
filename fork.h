#pragma once

#include <string>
#include <semaphore.h>


struct  shared_data_t
{
    pthread_mutex_t mutex;
    long refCount;
};


class Fork{
    std::string semName;
    std::string shmName;
    sem_t *sem;
    shared_data_t *sharedData;

public:
    explicit Fork(std::string name);
    ~Fork();

    void post();
    void wait();

private:
    void mapSharedMemoryToProcessVirtualAddressSpace(int shm);

    void initSharedMemory();
};
