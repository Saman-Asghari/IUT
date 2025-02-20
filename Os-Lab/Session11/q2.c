#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>


int *readCount, *source;
sem_t *readSem, *sourceSem;

void writerprocess(int id) {
    while (1) {
        printf("[Writer %d] wants to write.\n", id);
        sem_wait(sourceSem);
        (*source)++;
        printf("[Writer %d] writes %d\n", id, *source);
        sleep((rand() % 3) + 1);
        sem_post(sourceSem);
        sleep((rand() % 3) + 1);
    }
}

void readerprocess(int id) {
    while (1) {
        printf("[Reader %d] wants to read.\n", id);
        sem_wait(readSem);
        (*readCount)++;
        if (*readCount == 1) {
            sem_wait(sourceSem);
        }
        sem_post(readSem);
        printf("[Reader %d] Read shared data: %d\n", id, *source);
        sleep((rand() % 3) + 1);
        sem_wait(readSem);
        (*readCount)--;
        if (*readCount == 0) {
            sem_post(sourceSem);
        }
        sem_post(readSem);
        sleep((rand() % 3) + 1);
    }
}


int main() {
	
	void *shm = mmap(NULL, 2*sizeof(sem_t)+2*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANONYMOUS, -1, 0);
	readSem = (sem_t *) shm;
	sourceSem = (sem_t *) (shm+sizeof(sem_t));
	readCount = (int *) (shm+2*sizeof(sem_t));
	source = (int *) (shm+2*sizeof(sem_t)+sizeof(int));
	*readCount = 0;
	*source = 0;

	// To Do:
	// 1. Initialize the semaphores
	// 2. Create child processes and call (reader, writer) functions
	// 3. Destroy the semaphores
	int totalReaders, totalWriters;

    // Initialize semaphores
    sem_init(readSem,1,1);
    sem_init(sourceSem,1,1);

    printf("Enter number of readers: ");
    scanf("%d", &totalReaders);
    printf("Enter number of writers: ");
    scanf("%d", &totalWriters);

    // Create reader 
    for (int i = 0; i < totalReaders; i++) {
        if (fork() == 0) {
            srand(time(NULL) + getpid());
            readerprocess(i + 1);
            exit(0);
        }
    }

    // Create writer 
    for (int i = 0; i < totalWriters; i++) {
        if (fork() == 0) {
            srand(time(NULL) + getpid());
            writerprocess(i + 1);
            exit(0);
        }
    }

    // Wait for all child processes
    for (int i = 0; i < totalReaders + totalWriters; i++) {
        wait(NULL);
    }

    // semaphore destroying
    sem_destroy(readSem);
    sem_destroy(sourceSem);
	munmap(shm, 2*sizeof(sem_t)+2*sizeof(int));
		
}