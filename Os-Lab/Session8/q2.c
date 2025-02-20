
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
 
void log_elapsed_time(struct timeval start) {
    struct timeval stop;
    gettimeofday(&stop, NULL);
    long seconds = stop.tv_sec - start.tv_sec;
    float micro_start = start.tv_usec;
    float micro_stop = stop.tv_usec;
    long elapsed_ms = seconds * 1000 + (micro_stop - micro_start) / 1000;
    printf("Elapsed: %ld ms\n", elapsed_ms);
}
 
void child_task() {
    char args[2];
    args[1] = '\0';
    srand(time(0) + getpid());
    args[0] = (char)((rand()%5)+1+'0');
    execl("/home/oslab05/week8/app.out", "app", args, NULL);
    perror("execl failed");
    exit(1);
}
 
int main() {
    struct timeval start;
    while (1) {
        pid_t pid = fork();
        if (pid == 0) {
            child_task();
        } else if (pid > 0) {
            gettimeofday(&start, NULL);
        } 
        wait(NULL);
        log_elapsed_time(start);
    }
 
    return 0;
}
