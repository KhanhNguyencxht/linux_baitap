#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int counter = 0;

int ret_SIGINT  = 0;
int ret_SIGUSR1 = 0;
int ret_SIGUSR2 = 0;

void hanler1();
void hanler2();
void hanler3();

int main() {
    /* nhan ctrl c in ra thong diep bat ky*/
    if(SIG_ERR == signal(SIGINT, hanler1)) {
        printf("create SIGINT error \n");
        exit(1);
    }
    /* dang ky hoat dong cho SIGUSR1*/
    if(SIG_ERR == signal(SIGUSR1, hanler2)) {
        printf("create SIGUSR1 error \n");
    }
    /* dang ky hoat dong cho SIGUSR1*/
    if(SIG_ERR == signal(SIGUSR2, hanler2)) {
        printf("create SIGUSR2 error \n");
    }

    /* clear signal*/
    kill(ret_SIGINT,SIGINT);
    kill(ret_SIGUSR1,SIGUSR1);
    kill(ret_SIGUSR2,SIGUSR2);

    sleep(5);
    return 0;
}

void hanler1() {
    printf("hanler1() SIGINT, counter: %d \n", counter++);
    printf("PID ID: %d \n", getpid());
    ret_SIGINT = getpid();
}

void hanler2(int sig) {
    if(SIGUSR1 == sig) {
        printf("hanler2() SIGUSR1 \n");
        printf("PID ID: %d \n", getpid()); 
        ret_SIGUSR1 =  getpid();
    }

    if(SIGUSR2 == sig) {
        printf("hanler2() SIGUSR2 \n");
        printf("PID ID: %d \n", getpid()); 
        ret_SIGUSR2 =  getpid();
    }
}
