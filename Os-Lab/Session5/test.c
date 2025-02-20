#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include <string.h>
#include <errno.h>

#define device_path "/dev/saman_headphone"
#define buff_len 200

void playy(const char* massage){
	int fd=open(device_path,O_WRONLY);
	write(fd,massage,strlen(massage));

}

void recordd(int size){
	int fd=open(device_path,O_RDONLY);
	if(fd<0){
		printf("failed to open the file\n");
	}
	char* buffer=malloc(size);
	read(fd,buffer,size);
	printf("recorded : ");
	for(int i=0;i<size;i++){
		printf("%hhx",buffer[i]);
	}
	free(buffer);
	close(fd);
}

int main(void){
	recordd(50);
	recordd(83);
	recordd(12);
	playy("sadfsffasssssssssssssssssssssssssssssssssssdfadsfasfasfsfasfasfassdfsd");
	playy("opoposfdfdsfsdfsdfsdsdfsdrwqeyreygshfgasgfuywjgrjhgsytfuasgfuytwegjasgfygasdygfaysdgfuypopopo");	
	playy("opqyrgwehgfdsgufdhuasehfghqwrfgjhasdgfjgsufguawghfjasdjgfhsdgfjgasdjghfgfjaguop2odsfjfhkjasfdhkfjdhdkjdfhfsdakjhsdfsdkfjhdfskjsdfahsfdkajhsdfakjfasdsdfakjhsfadsfadkghklsfdajsgvjsdhasdfshasdfuisdahdskdjahfasds");

	return 0;
}
