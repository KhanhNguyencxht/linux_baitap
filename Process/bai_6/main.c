#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void waitpid_(int ret_PID, int ret_getpid);

/**
 * viet mot chuong trinh con A tao ra tien trinh con B
 * in ra PID va PPID cau chung
 * su dung system waitpid lay trang thai ket thuc cua tien trinh con B
*/

/* Cấp phát stack frame cho hàm main() */
int main(int argc, char const *argv[]){
    int a = 0;
    int ret_getpid = 0;
    int ret_getppid = 0;
    int ret_PID = 0;
    
    __pid_t pid;
    
    printf("gia tri cua a thoi dien hien tai: %d \n\n", a);
    pid = fork();
    
    /*tien trinh con*/
    if(0 == pid) {
        ret_getpid = getpid();
        ret_getppid = getppid();
        printf("Im the child process con a: %d \r\n", --a);
        printf("My PID is: %d, my parent PPID is: %d \n\n", ret_getpid, ret_getppid);
//        sleep(10);
//        while (1); // doi, terminal nhap lenh kill -9 PID esp ket thuc bat thuong
    }

    /*tien trinh cha*/
    else if(0 < pid) {
        printf("Im the child process cha a: %d \r\n", a);
        printf("My PID is: %d \r\n\r\n", getpid());
        
        /*lay PID va trng thai ket thuc cua chuong trinh con duoc chi dinh*/
        waitpid_(ret_PID, ret_getpid);
    }
    else{ 
        printf("fork error \r\n");
    }
    return 0;
}

/* lay PID va trng thai ket thuc cua chuong trinh con duoc chi dinh*/
void waitpid_(int ret_PID, int ret_getpid){
    int ret = 0;

    ret_PID = waitpid(ret_getpid, &ret, 0);
    if(-1 == ret_PID) {
        printf("wait() unsuccessfull \r\n");
     }

    printf("PID cua child process con: %d \n", ret_PID);

     /*chuong trinh con ket thuc binh thuong*/
    if(WIFEXITED(ret)) {
        printf("Child process normailly, value status: %d\n",  WEXITSTATUS(ret));
    }

    /*chuong trinh con ket thuc bat binh thuong*/
    else if(WIFSIGNALED(ret)) {
        printf("Child process was killed by signal, value status: %d\n",  WTERMSIG(ret));
    }
}