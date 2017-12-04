#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <zconf.h>
#include <cstring>

#include "fork.h"

Fork::Fork(std::string _name) : semName(_name), shmName(_name + "_shm") {
    if(SEM_FAILED == (sem = sem_open(semName.c_str(), O_CREAT, 0777, 1))) {
        perror(("semaphore " + semName + " open").c_str());
    }

    initSharedMemory();
}

void Fork::initSharedMemory() {
    int shm = 0;
    sharedData = new shared_data_t{};

    printf("ShmName: %s\n", shmName.c_str());
    if(-1 == (shm = shm_open(shmName.c_str(), O_CREAT | O_EXCL | O_RDWR, 0777))) {
        if(EEXIST == errno) {
            if(-1 == (shm = shm_open(shmName.c_str(), O_CREAT | O_RDWR, 0777))) {
                perror(("shared memory" + shmName + " open").c_str());
            }
            mapSharedMemoryToProcessVirtualAddressSpace(shm);

            printf("opening %s:%d before: %li\n", shmName.c_str(), shm, sharedData->refCount);
            pthread_mutex_lock(&sharedData->mutex);
            sharedData->refCount += 1;
            pthread_mutex_unlock(&sharedData->mutex);
            printf("opening %s:%d after: %li\n", shmName.c_str(), shm, sharedData->refCount);
        }
    }
    else {
        if (ftruncate(shm, sizeof(long)) == -1) {
            perror("ftruncate");
        }

        mapSharedMemoryToProcessVirtualAddressSpace(shm);

        printf("creating %s:%d before: %li\n", semName.c_str(), shm, sharedData->refCount);
        pthread_mutex_lock(&sharedData->mutex);
        sharedData->refCount += 1;
        pthread_mutex_unlock(&sharedData->mutex);
        printf("creating %s:%d after: %li\n", shmName.c_str(), shm, sharedData->refCount);
    }
}

void Fork::mapSharedMemoryToProcessVirtualAddressSpace(int shm) {
    sharedData = (shared_data_t *) mmap(nullptr, sizeof(long), PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    if (sharedData == (shared_data_t *) -1) {
        perror("mmap");
    }
    close(shm);
}

Fork::~Fork() {
    printf("destructor %s before %li\n", semName.c_str(), sharedData->refCount);
    pthread_mutex_lock(&sharedData->mutex);
    sharedData->refCount -= 1;
    pthread_mutex_unlock(&sharedData->mutex);
    printf("destructor %s after %li\n", shmName.c_str(), sharedData->refCount);

    if(0 == sharedData->refCount) {
        printf("unlinking\n");
        shm_unlink(shmName.c_str());
        sem_unlink(semName.c_str());
    }
}

void Fork::wait() {
    sem_wait(sem);
}

void Fork::post() {
    sem_post(sem);
}
