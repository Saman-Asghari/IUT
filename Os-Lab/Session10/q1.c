#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <signal.h>

void handler1(int signo, siginfo_t *sign)
{
    printf("%p is the address ---:::)))\n", sign->si_addr);
    exit(1);
}

int main()
{
    struct sigaction action1;
    action1.sa_handler = handler1;
    action1.sa_flags = 0;
    int arr[3];
    sigaction(SIGSEGV, &action1, NULL);
    printf("%d", arr[3000000]);
    return 0;
}