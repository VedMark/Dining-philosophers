#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	sem_unlink("/fork0");
	sem_unlink("/fork1");
	sem_unlink("/fork2");
	sem_unlink("/fork3");
	sem_unlink("/fork4");
	shm_unlink("/fork0_shm");
        shm_unlink("/fork1_shm");
        shm_unlink("/fork2_shm");
        shm_unlink("/fork3_shm");
        shm_unlink("/fork4_shm");

	return 0;
}

