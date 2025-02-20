#include<stdio.h>
#include<stdlib.h>
#include "prime.h"
int main(int argc,char* argv[]){
	for(int i=1;i<argc;i++){
		int number=atoi(argv[i]);
		if(prime(number)){
			printf("the number is prime\n");
		}
		else{
			printf("the number is not prime\n");
		}
}
return 0;

}