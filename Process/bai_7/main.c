#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void signal_hanlel();

/**
 * ngan zombie hinh thanh khi tien tinh con mat truoc chuong trinh cha
 * su dung SIGCHLD
*/

int main(int argc, char const *argv[]) {
    pid_t child_pid;

    child_pid = fork();
    if(0 == child_pid) {
        printf("child process con \n");
        printf("MY PID: %d, parent PPID: %d \n\n", getpid(), getppid());
    //    while(1);
    }

    /**
     * signal dung de bat tin hieu va xu ly chuong trinh
     * SIGCHLD la tin hieu canh bao gui ve khi tien trinh con sap ket thuc
     * signal_hanlel ham xu ly chuong trinh
     * */
    else if(0 < child_pid) {
        signal(SIGCHLD, signal_hanlel);

        printf("child process cha \n");
        printf("parent PPID: %d \n\n",  getpid());
        while (1);
    }
    else{
        printf("fork error \n");
    }
}

void signal_hanlel() {
    int status = 0;
    printf("process con sap ket thuc \n");
    /* doi chuong trinh con ket thuc*/
    wait(NULL);
    printf("process con status: %d \n", status);
}