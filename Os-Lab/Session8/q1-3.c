
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
 
#define MAX_CHILDREN 5
 
long long int child_pids[MAX_CHILDREN];
 
 
void task(int id) {
    srand((time(0)+id));
    int random_number=rand()%5+1; 
    struct timeval start, current;
    gettimeofday(&start,NULL);
    while (1) {
        gettimeofday(&current, NULL);
        long elapsed = (current.tv_sec-start.tv_sec);
        if (elapsed >= random_number) {
            break;
        }
    }
    
    printf("task <%d> completed by child <%d> in <%d> seconds\n",id, getpid(),random_number );
    exit(0);
}
 
int main() {
    
    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            task(i);
        } else if (pid > 0) {
            child_pids[i] = pid;
        } 
    }
 
 
    while (1) {
        for (int i = 0; i < 5; i++) {
            pid_t pid = waitpid(child_pids[i], NULL, WNOHANG);
            if (pid > 0) {
 
                pid_t new_pid = fork();
                if (new_pid == 0) {
                    task(i);
                } else if (new_pid > 0) {
                    child_pids[i] = new_pid;
                }
            }
        }
        sleep(5);
    }
 
    printf("finishted.\n");
    return 0;
}
