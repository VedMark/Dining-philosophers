#pragma once


#include <string>
#include <utility>
#include <semaphore.h>
#include <fcntl.h>

class Fork{
    std::string name;
    sem_t *sem;

public:
    Fork();
    explicit Fork(std::string name);
    Fork(const Fork &);
    ~Fork() = default;
    Fork& operator=(const Fork&) = default;

    std::string getSemName();
    sem_t *getSem();
};

