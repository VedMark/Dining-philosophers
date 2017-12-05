#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <zconf.h>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "fork.h"

Fork::Fork(const std::string &_name, const std::string &_owner, const Logger &_logger) :
        forkName(_name), shmName(_name + "_shm"), owner(_owner), logger(_logger) {

    if(SEM_FAILED == (sem = sem_open(forkName.c_str(), O_CREAT, 0777, 1))) {
        logger->error(strerror(errno));
    }

    initSharedMemory();
}

void Fork::initSharedMemory() {
    int shm = 0;

    if(-1 == (shm = shm_open(shmName.c_str(), O_CREAT | O_EXCL | O_RDWR, 0777))) {
        if(EEXIST == errno) {
            if(-1 == (shm = shm_open(shmName.c_str(), O_CREAT | O_RDWR, 0777))) {
                logger->error(strerror(errno));
            }
            mapSharedMemoryToProcessVirtualAddressSpace(shm);

            pthread_mutex_lock(&sharedData->mutex);
            sharedData->refCount += 1;
            pthread_mutex_unlock(&sharedData->mutex);
        }
    }
    else {
        if (ftruncate(shm, sizeof(long)) == -1) {
            logger->error(strerror(errno));
        }

        mapSharedMemoryToProcessVirtualAddressSpace(shm);

        pthread_mutex_lock(&sharedData->mutex);
        sharedData->refCount = 1;
        pthread_mutex_unlock(&sharedData->mutex);

        logger->info(owner + " created " + forkName);
    }
}

void Fork::mapSharedMemoryToProcessVirtualAddressSpace(int shm) {
    sharedData = (shared_data_t *) mmap(nullptr, sizeof(long), PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    if (sharedData == (shared_data_t *) -1) {
        logger->error(strerror(errno));
    }
    close(shm);
}

Fork::~Fork() {
    pthread_mutex_lock(&sharedData->mutex);
    sharedData->refCount -= 1;
    pthread_mutex_unlock(&sharedData->mutex);

    if(0 == sharedData->refCount) {
        logger->info(owner + " destroyed " + forkName);
        shm_unlink(shmName.c_str());
        sem_unlink(forkName.c_str());
    }
    munmap(sharedData, sizeof(shared_data_t));
}

void Fork::post() {
    sem_post(sem);
    logger->info(owner + " put " + forkName);
}

void Fork::wait(std::time_t start_time) {
    sem_wait(sem);
    auto end_time = std::time(nullptr);
    logger->info(owner + " got " + forkName + " after " + std::to_string(end_time - start_time) + "s of waiting");
}
