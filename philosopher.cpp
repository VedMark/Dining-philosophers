#include <iostream>
#include <random>
#include <utility>
#include <zconf.h>
#include <spdlog/spdlog.h>

#include "philosopher.h"

Philosopher::Philosopher(char *_name, const std::string &_lForkName, const std::string &_rForkName, const Logger &pLogger)
        :
        name(_name),
        logger(pLogger),
        lFork(_lForkName, name, pLogger),
        rFork(_rForkName, name, pLogger) {}

void Philosopher::exist() {
    FOREVER_BEGIN
        logger->info(name + " got hungry");

        lFork.wait(std::time(nullptr));
        rFork.wait(std::time(nullptr));

        eat();

        lFork.post();
        rFork.post();

        reflex();

        if(getRandomUInt(1, 5) == 5) {
            break;
        }
    FOREVER_END
}

void Philosopher::eat() const{
    logger->info(name + " started eating");

    takeTime(4, 8);

    logger->info(name + " finished eating");
}

void Philosopher::reflex() const{
    logger->info(name + " started reflexing");

    takeTime(1, 4);

    logger->info(name + " finished reflexing");
}

void Philosopher::takeTime(unsigned begin, unsigned end) const{
    sleep(getRandomUInt(begin, end));
}

unsigned Philosopher::getRandomUInt(unsigned begin, unsigned end) const{
    if(begin > end) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return static_cast<unsigned int>(dis(gen));
}
