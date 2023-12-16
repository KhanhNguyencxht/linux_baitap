#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void hanler_sigint();

int main() {
sigset_t new_set;
sigset_t old_set;

    if(SIG_ERR == signal(SIGINT,hanler_sigint)) {
        printf("create SIGINT error \n");
        exit(1);
    }
    /* khoi tao va lam emty mat na(mask) set 0 */
    sigemptyset(&new_set);
    /* old_set lay ra du lieu hien tai cua current mask*/
    sigemptyset(&old_set);
    /* set tin hieu(block_mask) duoc chi dinh boi SIGINT*/
    sigaddset(&new_set, SIGINT);
    printf("new_set is %d \n", new_set);
    printf("old_set is %d \n", old_set);
    /* thay doi gia tri new_set theo gia tri SIG_BLOCK, old_set*/
    if(0 == sigprocmask(SIG_BLOCK, &new_set, &old_set)) {
        printf("block SIGINT \n");
        /** kiem tra SIGINT co trong new_set khong cos thi return 1
         * khi bi chan block thi Ctrl+c se bi chan khong chay duoc
        */
        if(1 == sigismember(&new_set, SIGINT)) {
            printf("SIGINT is blocked!\n");
            sleep(5); 
        }
        else if(0 == sigismember(&new_set, SIGINT)) {
            printf("SIGINT is unblocked!\n");
            sleep(5);
        }
    }
    /* thay doi gia tri new_set theo gia tri SIG_UNBLOCK, old_set*/
    if(0 == sigprocmask(SIG_UNBLOCK, &new_set, &old_set)) {
        printf("unblock SIGINT \n");
        /* kiem tra SIGINT co trong new_set khong co thi return 1*/
        if(1 == sigismember(&new_set, SIGINT)) {
            printf("SIGINT is unblocked!\n");
        }
        else if(0 == sigismember(&new_set, SIGINT)) {
            printf("SIGINT is blocked!\n");
            sleep(5);
        }
    }

    kill(getpid(), SIGINT);
    sleep(5);
}
void hanler_sigint() {
    printf("SIGINT PID ID: %d \n", getpid());
}

