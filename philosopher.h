#pragma once

#include "fork.h"
#include <spdlog/spdlog.h>

using Logger = std::shared_ptr<spdlog::logger>;

#define FOREVER_BEGIN for(;;) {
#define FOREVER_END }

class Philosopher {
    std::string name;
    Fork lFork;
    Fork rFork;
    Logger logger;

public:
    explicit Philosopher(char *_name, const std::string &_lForkName, const std::string &, const Logger &pLogger);
    ~Philosopher() = default;

    void exist();

private:
    void eat();
    void reflex() const ;
    void takeTime(unsigned int begin, unsigned int end) const;
    unsigned getRandomUInt(unsigned begin, unsigned end) const;
};
