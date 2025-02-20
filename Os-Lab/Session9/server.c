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

#define MAX_CLIENTS 5

typedef struct
{
    pid_t pid;
    int temperature;

} TemperatureData;

int main()
{
    unlink(PIPE_NAME);
    if (mkfifo(PIPE_NAME, 0777) == -1)
    {
        perror("Failed to create pipe");
        return 1;
    }
    int pipe_fd;
    int min_temp = 1e8;
    while (1)
    {
        pipe_fd = open(PIPE_NAME, O_RDONLY);
        if (pipe_fd == -1)
        {
            perror("Failed to open pipe");
            return 1;
        }
        TemperatureData data;
        if (read(pipe_fd, &data, sizeof(TemperatureData)) > 0)
        {
            printf("from client (PID: %d): Temperature = %d\n",data.pid, data.temperature);
            if (data.temperature < min_temp)
            {
                min_temp = data.temperature;
                printf("New minimum temperature: %d\n", min_temp);
            }
            else
            {
                printf("Current minimum temperature remains: %d\n", min_temp);
            }
        }
        close(pipe_fd);
        pipe_fd = open(PIPE_NAME, O_WRONLY);
        if (pipe_fd == -1)
        {
            perror("Failed to open pipe for writing");
            return 1;
        }
        write(pipe_fd, &min_temp, sizeof(min_temp));
        close(pipe_fd);
    }
    return 0;
}
