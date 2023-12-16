#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

pthread_t thread_id1;
pthread_t thread_id2;
pthread_t thread_id3;

char signal_fle[] = "signal.txt";
char multi_fle[] = "multi.txt";

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    int counter;
    int time;
} timess_;


static void *signal(void *info);

int signal_thread();
int multi_thread();


int main() {
    signal_thread();
    multi_thread();
    return 0;
}


static void *signal(void *agsv)  {
    timess_ *a =(timess_*) agsv;
    char buf[15] = {0};

    pthread_t thread_id = pthread_self(); 
    pthread_mutex_lock(&lock);

    printf("signal thread id1: %ld \n", thread_id);
    /* open file text1.txt*/
    int fd = open(signal_fle, O_WRONLY);
    if(-1 == fd)
        printf("open file error \n");    
    for(int i=0; i < 1000000; i++) {
        a->counter++;
        sprintf(buf, "%d \n", a->counter);
        /* write data in file*/
        int w = write(fd, buf, sizeof(buf));
        if(-1 == w)
            printf("write error \n");
        
    }
    /*close file*/
    close(fd);
    pthread_mutex_unlock(&lock);
}

static void *multi1(void *agsv)  {
    timess_ *a =(timess_*) agsv;
    char buf[15] = {0};

    pthread_t thread_id = pthread_self(); 
    pthread_mutex_lock(&lock);

    printf("signal thread id2: %ld \n", thread_id);
    /* open file text1.txt*/
    int fd = open(multi_fle, O_WRONLY);
    if(-1 == fd)
        printf("open file error \n");    
    for(int i=0; i < a->time; i++) {
        a->counter++;
        sprintf(buf, "%d \n", a->counter);
        /* write data in file*/
        int w = write(fd, buf, sizeof(buf));
        if(-1 == w)
            printf("write error \n");
        
    }
    /*close file*/
    close(fd);
    pthread_mutex_unlock(&lock);
}

static void *multi2(void *agsv)  {
    timess_ *a =(timess_*) agsv;
    char buf[15] = {0};

    pthread_t thread_id = pthread_self(); 
    pthread_mutex_lock(&lock);

    printf("signal thread id3: %ld \n", thread_id);
    /* open file text1.txt*/
    int fd = open(signal_fle, O_WRONLY);
    if(-1 == fd)
        printf("open file error \n");    
    for(int i=0; i < a->time; i++) {
        a->counter++;
        sprintf(buf, "%d \n", a->counter);
        /* write data in file*/
        int w = write(fd, buf, sizeof(buf));
        if(-1 == w)
            printf("write error \n");
        
    }
    /*close file*/
    close(fd);
    pthread_mutex_unlock(&lock);
}


int signal_thread() {
    int ret = 0;
    
    timess_ test = {0};
    /* take time start*/   
    clock_t First = clock();
    /* create file */
    int fd = open(signal_fle, O_CREAT | O_RDWR | O_APPEND, 0667);
    close(fd);
    if(-1 == fd)
        printf(" create file error \n");
    /**/
    if(ret = pthread_create(&thread_id1, NULL, &signal, &test)) {
        printf("pthread create thread id1 error, status = %d \n", ret);
    }
    /* wait thread_id1 intermetion*/
    pthread_join(thread_id1, NULL);
    /* write couter in file */
    


    /* take time final*/
    clock_t final = clock();
    double used = ((double)(final - First)) / CLOCKS_PER_SEC;
    printf("counter: %d \n", test.counter);
    printf("time user single thread : %f \n\n", used);
}

int multi_thread() {
    int ret = 0;

    timess_ test = {0};
    test.counter = 0;
    test.time = 500000;

    int fd = open(multi_fle, O_CREAT | O_RDWR | O_APPEND, 0667);
    close(fd);
    if(-1 == fd)
        printf(" create file error \n");
    
    clock_t First = clock();

    if(ret = pthread_create(&thread_id2, NULL, &multi1, &test)) {
        printf("pthread create thread id1 error, status = %d \n", ret);
    }

    if(ret = pthread_create(&thread_id3, NULL, &multi2, &test)) {
        printf("pthread create thread id1 error, status = %d \n", ret);
    }
    /* wait thread ket thuc*/
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);
    printf("counter: %d \n", test.counter);

   clock_t final = clock();
   double used = ((double)(final - First)) / CLOCKS_PER_SEC;
   printf("time user multi thread : %f \n\n", used);
}

