#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	sem_unlink("/fork0");
	sem_unlink("/fork1");
	sem_unlink("/fork2");
	sem_unlink("/fork3");
	sem_unlink("/fork4");
	
	return 0;
}

