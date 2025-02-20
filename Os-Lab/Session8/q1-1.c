
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
 
#define MAXCHILD 5
typedef long long ll;
void task(int id){
 
    srand(time(0)+id);
    int random_number=rand()%5+1;
    sleep(random_number);
    printf("Task <%d> has been done by child <%ld> in <%d> seconds\n",id,getpid(),random_number);
    exit(0);
}
 
int main(){
    for(ll i=0;i<MAXCHILD;i++){
 
        if(!fork()){
            task(i);
        }
    }
 
    for(ll i=0;i<MAXCHILD;i++){
        wait();
    }
    printf("end of program\n");
 
 
}
