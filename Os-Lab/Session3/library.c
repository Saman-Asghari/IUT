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

void createFileWithPermission(const char * path, int permission){
    umask(0);
    unlink(path);
    int file_disciptor=open(path,O_CREAT | O_WRONLY,permission);
    close(file_disciptor);
    printf("file has created in %s \n",path);

}

void checkFile(const char * path, int permission){
    int res=0;
    if(access(path,X_OK)==0){
        res+=1;
    }
    if(access(path,W_OK)==0){
        res+=2;
    }
    if(access(path,R_OK)==0){
        res+=4;
    }

    if((permission & res)==permission){
        printf("The file permission has the same as the same you gave\n");
    }
    else{
        printf("\npermission: %d\n",res);
    }
}

void showFileInfo(const char * path){
    struct stat fstats;
    stat(path,&fstats);
    uid_t user_id=fstats.st_uid;
    time_t time=fstats.st_mtime;
    off_t size=fstats.st_size;

    char* real_time=ctime(&time);
    printf("user id %u\n last modified time: %s\n file size : %ld\n",user_id,real_time,size);

}

void createFileList(const char * dirPath, const char * prefix, const char * ext, int from, int to){
    char name[300];
    umask(0);
    for(int i=from;i<=to;i++){
        sprintf(name,"%s/%s_%d.%s",dirPath,prefix,i,ext);
        int fd=open(name,0755);
        close(fd);
        printf("%s\n",name);
    }
}




