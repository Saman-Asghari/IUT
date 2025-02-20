#include<stdio.h>
#include "prime.h"
int prime(int n){
	if(n<=1) return 0;
	if(n==2) return 1;
	int counter=0;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}