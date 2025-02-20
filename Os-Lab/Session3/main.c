#include "library.h"
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

int main(int argc,char* argv[]){
    if(!strcmp(argv[1],"-c")){
        int permission=strtol(argv[3],0,8);
        createFileWithPermission(argv[2],permission);
    }

    if(!strcmp(argv[1],"-t")){
        int permission=strtol(argv[3],0,8);
        checkFile(argv[2],permission);
    }
    if(!strcmp(argv[1],"-s")){
        showFileInfo(argv[2]);
    }

    if(!strcmp(argv[1],"-m")){
        createFileList(argv[2],argv[3],argv[4],atoi(argv[5]),atoi(argv[6]));
    }
}