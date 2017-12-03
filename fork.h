#pragma once

#include <string>
#include <semaphore.h>

class Fork{
    std::string semName;
    std::string shmName;
    sem_t *sem;
    long *refCount;

public:
    explicit Fork(std::string name);
    Fork(const Fork &);
    ~Fork();
    Fork& operator=(const Fork&) = default;

    void post();
    void wait();
};

