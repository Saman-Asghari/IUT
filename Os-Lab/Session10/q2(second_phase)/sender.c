#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "protocol.h"

int main(int argc, char *argv[])
{
    shm_unlink(NAME);

    srand(time(NULL));
    pid_t pidviwer = atoi(argv[1]);
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    int size = NUM * ARRAY_S;

    ftruncate(fd, size);

    void *data = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == (void *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    printf("sender address: %p\n", data);
    struct player *array = (struct player *)data;
    // write array in shared memory
    for (int i = 0; i < NUM - 1; i++)
    {
        sprintf(array[i].player_name, "plpayer ", i + 1);
        array[i].score = rand() % 100 + 1;
    }
    while (1)
    {
        pid_t pid;
        for (int i = 0; i < NUM; i++)
        {
            pid = fork();
            if (pid == 0)
            {
                srand(time(NULL) * getpid());
                for (int j = i; j < NUM; j += NUM)
                {
                    array[j].score = rand() % 100 + 1;
                }

                exit(1);
            }
        }

        for (int i = 0; i < NUM; i++)
        {
            wait(NULL);
        }

        kill(pidviwer, SIGUSR1);

        sleep(3);
    }

    munmap(data, size);

    close(fd);
    return EXIT_SUCCESS;
}