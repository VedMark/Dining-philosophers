#include <iostream>
#include <random>
#include <zconf.h>

#include "philosopher.h"

Philosopher::Philosopher(std::string _name, const std::string &_lForkName, const std::string &_rForkName) :
        name(std::move(_name)), lFork(_lForkName), rFork(_rForkName) {}

void Philosopher::exist() {
    lFork.wait();
    rFork.wait();

    eat();

    lFork.post();
    rFork.post();

    reflex();
}

void Philosopher::eat() {
    std::cout << name << " started eating" << std::endl;

    takeTime();

    std::cout << name << " finished eating" << std::endl;
}

void Philosopher::reflex() {
    std::cout << name << " started reflexing" << std::endl;

    takeTime();

    std::cout << name << " finished reflexing" << std::endl;
}

void Philosopher::takeTime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    sleep(static_cast<unsigned int>(dis(gen)));
}
