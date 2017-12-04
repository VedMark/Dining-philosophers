#pragma once

#include "fork.h"

#define FOREVER_BEGIN for(;;) {
#define FOREVER_END }

class Philosopher {
    std::string name;
    Fork lFork;
    Fork rFork;

public:
    explicit Philosopher(std::string _name, const std::string &_lForkName, const std::string &_rForkName);
    ~Philosopher() = default;

    void exist();

private:
    void eat() const;
    void reflex() const ;
    void takeTime() const ;
    unsigned getRandomUInt(unsigned begin, unsigned end) const;
};
