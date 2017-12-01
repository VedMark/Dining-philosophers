#pragma once

#include "fork.h"

class Philosopher {
    u_long id;
    std::string name;
    Fork lFork;
    Fork rFork;

public:
    explicit Philosopher(u_long id, std::string _name, const Fork &lFork, const Fork &rFork);
    Philosopher(const Philosopher &that);

    void exist();

private:
    void eat();
    void reflex();
    void takeTime();
};
