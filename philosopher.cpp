#include <iostream>
#include <random>
#include <utility>
#include <zconf.h>

#include "philosopher.h"

Philosopher::Philosopher(std::string _name, const std::string &_lForkName, const std::string &_rForkName) :
        name(std::move(_name)), lFork(_lForkName), rFork(_rForkName) {}

void Philosopher::exist() {
    FOREVER_BEGIN
        lFork.wait();
        rFork.wait();

        eat();

        lFork.post();
        rFork.post();

        reflex();

        if(getRandomUInt(1, 5) == 5) {
            exit(0);
        }
    FOREVER_END
}

void Philosopher::eat() const{
    std::cout << name << " started eating" << std::endl;

    takeTime();

    std::cout << name << " finished eating" << std::endl;
}

void Philosopher::reflex() const{
    std::cout << name << " started reflexing" << std::endl;

    takeTime();

    std::cout << name << " finished reflexing" << std::endl;
}

void Philosopher::takeTime() const{
    sleep(getRandomUInt(1, 5));
}

unsigned Philosopher::getRandomUInt(unsigned begin, unsigned end) const{
    if(begin > end) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return static_cast<unsigned int>(dis(gen));
}
