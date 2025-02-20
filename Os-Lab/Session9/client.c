#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define PIPE_NAME "/tmp/temperature_pipe"

typedef struct
{
    pid_t pid;
    int temperature;
} TemperatureData;

int main()
{
    srand(time(NULL));
    while (1)
    {
        TemperatureData data;
        data.pid = getpid();
        data.temperature = rand() % 41; //
        int pipe_fd = open(PIPE_NAME, O_WRONLY);
        if (pipe_fd == -1)
        {
            perror("Failed to open pipe for writing");
            return 1;
        }
        write(pipe_fd, &data, sizeof(data));
        printf("Sent from producer (PID: %d): Temperature = %d\n", data.pid, data.temperature);
        close(pipe_fd);
        pipe_fd = open(PIPE_NAME, O_RDONLY);
        if (pipe_fd == -1)
        {
            perror("Failed to open pipe for reading");
            return 1;
        }
        int min_temp;
        read(pipe_fd, &min_temp, sizeof(min_temp));
        printf("Producer (PID: %d) received minimum temperature: %d\n", data.pid, min_temp);
        close(pipe_fd);
        sleep(3);
    }
    return 0;
}
