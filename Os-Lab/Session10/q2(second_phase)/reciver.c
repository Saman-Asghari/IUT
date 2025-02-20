#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

void handler1(int signo, siginfo_t *sign)
{
    printf("%p is the address ---:::)))\n", sign->si_addr);
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    int size = NUM * ARRAY_S;

    void *data = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == (void *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    struct player *array = (struct player *)data;

    printf("reciver address: %p\n", data);

    for (int i = 0; i < NUM - 1; i++)
    {
        printf("the name is %s and the score is %d\n", array[i].player_name, array[i].score);
    }
    munmap(data, size);
    close(fd);
}

int main()
{
    struct sigaction action1;
    action1.sa_handler = handler1;
    action1.sa_flags = 0;
    sigaction(SIGUSR1, &action1, NULL);
    printf("%d", getpid());
    fflush(stdout);
    while (1)
    {
        pause();
    }

    // delete file
    shm_unlink(NAME);
    return 1;
}