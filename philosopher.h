#pragma once

#include "fork.h"

class Philosopher {
    std::string name;
    Fork lFork;
    Fork rFork;

public:
    explicit Philosopher(std::string _name, const std::string &_lForkName, const std::string &_rForkName);

    void exist();

private:
    void eat();
    void reflex();
    void takeTime();
};
