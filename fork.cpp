#include <sys/mman.h>
#include <fcntl.h>
#include <utility>
#include <zconf.h>
#include <cstring>

#include "fork.h"

Fork::Fork(std::string _name) : semName(std::move(_name)), shmName(_name + "_shm") {
    if(SEM_FAILED == (sem = sem_open(semName.c_str(), O_CREAT, 0777, 1))) {
        perror(("semaphore " + semName + " open").c_str());
    }

    int shm = 0;
    if(-1 == (shm = shm_open(semName.c_str(), O_CREAT | O_RDWR, 0777))) {
        perror(("shared memory" + shmName + " open").c_str());
    }

    if ( ftruncate(shm, sizeof(long)) == -1 ) {
        perror("ftruncate");
    }

    printf("refCount to %s: %li\n", semName.c_str(), *refCount);
    void *ptr = mmap(nullptr, sizeof(long), PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    refCount = static_cast<long *>(ptr);
    printf("ptr = %p\n", ptr);
    printf("refCount = %p\n", refCount);
    long a = 1;
    //memcpy(ptr, &a, sizeof(long));
}

Fork::Fork(const Fork &that) {
    semName = that.semName;;
    shmName = that.shmName;
    sem = that.sem;
    *refCount = *that.refCount + 1;
}

Fork::~Fork() {
    *refCount -= 1;
    if(0 == *refCount) {
        printf("unlinking");
        shm_unlink(shmName.c_str());
        sem_unlink(semName.c_str());
    }
    delete refCount;
}

void Fork::wait() {
    sem_wait(sem);
}

void Fork::post() {
    sem_post(sem);
}
