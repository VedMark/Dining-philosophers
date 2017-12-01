#include "fork.h"

Fork::Fork() : name(), sem(nullptr) {

}

Fork::Fork(std::string _name) : name(std::move(_name)) {
    if(SEM_FAILED == (sem = sem_open(name.c_str(), O_CREAT, 0777, 1))) {
        perror(("semaphore " + name + " open").c_str());
    }
}

Fork::Fork(const Fork &that) {
    name = that.name;
    sem = that.sem;
}

std::string Fork::getSemName() {
    return name;
}

sem_t *Fork::getSem() {
    return sem;
}
