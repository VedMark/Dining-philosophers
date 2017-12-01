#include <iostream>
#include <random>
#include <zconf.h>
#include "philosopher.h"

Philosopher::Philosopher(u_long _id, std::string _name, const Fork &_lFork, const Fork &_rFork) :
        id(_id), name(std::move(_name)), lFork(_lFork), rFork(_rFork) {}

Philosopher::Philosopher(const Philosopher &that) {
    id = that.id;
    name = that.name;
    lFork = that.lFork;
    rFork = that.rFork;
}

void Philosopher::exist() {
    sem_wait(lFork.getSem());
    sem_wait(rFork.getSem());

    eat();

    sem_post(lFork.getSem());
    sem_post(rFork.getSem());

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