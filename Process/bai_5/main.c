#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * -viet chuong trinh con A tao ra tien trinh con B
 * -My pid(ma dinh danh): tien trinh con =  My PID tien trinh cha +1
 * -trong chuong trinh, tien trinh cha chay truoc va mat di
 * nen parent PID cua tien tinh con la cua system init = 1
*/

int main(int argc, char const *argv[]){
    int a = 0;
    __pid_t pid;
    
    printf("gia tri khoi tao cua a la: %d \r\n", a);
    pid = fork();
    /*tien trinh con*/
    if(0 == pid){
        printf("Im the child process con a: %d \r\n", --a);
        printf("My PID is: %d, my parent PID is: %d \r\n", getpid(), getppid());
    }
    /*tien trinh cha*/
    else if(0 < pid){
        printf("Im the parent process cha: %d \r\n", a);
        printf("My PID is: %d \r\n\r\n", getpid());
    }
    else{
        printf("fork() error \r\n");
    }
    return 0;
}
