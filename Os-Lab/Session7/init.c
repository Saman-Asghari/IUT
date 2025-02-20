#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

struct process_info{
    char state_str[16];
    unsigned long memory_usage;
    char name[32];
};


int main(void) {
	int pid;
			struct process_info test;

	while (1){
		scanf("%d",&pid);
		int temp=syscall(548,pid,&test);
		if(temp==0){
			printf("process id %d \n",pid);
			printf("process situation is %s\n ",test.state_str);
			printf("process memory usage %lu\n",test.memory_usage);
			printf("process name %s\n",test.name);
			fflush(stdout);
		}
		else{
			printf("failed!!!\n");
		}
	}
	return 0;
}
