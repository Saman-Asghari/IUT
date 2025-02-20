
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

#define MAX 5

long fac(int start, int end)
{
    long result = 1;
    for (int i = start; i <= end; i++)
    {
        result=result*i;
    }
    return result;
}

int main()
{

    int number;
    printf("Enter your number");
    fflush(stdout);
    scanf("%d", &number);
    int fd[2];
    int range=number/MAX; 
    printf("%d %d ",number,range);
    fflush(stdout);
    pid_t pid;
    if(pipe(fd)==-1){
        printf("Failed!!!\n");
        return -1;
    }
    for (int i = 0; i < MAX; i++)
    {
        pid = fork();
        if (pid == 0)
        { 
            close(fd[0]);
            int start=i*range+1;
            int end=(i==MAX-1)?number:(i+1)*range;
            long result= fac(start,end);
            write(fd[1], &result, sizeof(result));
            close(fd[1]);
            exit(0);
        }
    }
    close(fd[1]);
    long final_result = 1;
    for (int i=0;i<MAX;i++)
    {
        long child_result;
        read(fd[0], &child_result, sizeof(child_result));
        printf("child-%d: %ld\n", i + 1, child_result);
        final_result *= child_result;
    }
    close(fd[0]);
    printf("fac of %d = %ld\n", number, final_result);
    for (int i = 0; i < MAX; i++)
    {
        wait();
    }
    return 0;
}
