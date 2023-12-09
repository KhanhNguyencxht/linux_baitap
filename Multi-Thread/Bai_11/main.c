#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1;
pthread_t thread_id2;
pthread_t thread_id4;
pthread_t thread_id5;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int counter = 0;

typedef struct
{
    char name[20];
    char quequan[50];
    int namsinh;
    double sdt;
} thr_data_t;

static void *thr_hanle1(void *args);
static void *thr_hanler2(void *args);
static void *thr_hanler3(void *args);
static void *thr_hanler4(void *args);

int thread_create();
void ngan_zombie();
int thread_lock();

int main(int argc, char const *argv[]){
    /**
     * tao 2 thread chung mot hanler
     * kiem tra neu thread 1 thif in ra tong diep bat ky
     * thread 2 truyen vao du lieu kieu struct human khoi tao tu truoc
     * cac thong tin: ho ten, nam sinh. quen quan, sdt
     * in ra man hinh
    */
//    thread_create();

    /**khoa thread de thuc hien cac bien toan cuc dung chung
     * tranh nhieu thread cung 1 luc su dung chung bien toan cuc
    */
    thread_lock();
    

    /**
     * ngan zombie hinh thanh su dung ham doi ket thuc pthread_joi
     * hoac pthread_detach ket thuc chuong trinh tu dong
    */
//    ngan_zombie();
    sleep(5);
//    while (1);

    return 0;
}

static void *thr_hanle1(void *args){
    pthread_t thread_id = pthread_self();
    thr_data_t *data = (thr_data_t *)args;

    if(pthread_equal(thread_id, thread_id1)) {
        printf("thread1 dang chay \n\n");
    }
    else if(pthread_equal(thread_id, thread_id2)){
        printf("thread2 dang chay \n");
        printf("name: %s ; nam sinh: %d ; so dien thoai: %d ; que quan: %s \n\n", 
       data->name, data->namsinh, (int)data->sdt, data->quequan);
       while(1){
        printf("thread2 test \n");
        sleep(1);
       }
    }
} 

int thread_create(){
        int ret = 0;
    thr_data_t data = {0};
    data.namsinh = 1996;
    data.sdt = 985892698;
 
    strncpy(data.name, "Nguyen Dinh Khanh", sizeof(data.name));
    strncpy(data.quequan, "Cam Hung, Cam Xuyen, Ha Tinh", sizeof(data.quequan));
    
    if(ret = pthread_create(&thread_id1, NULL, &thr_hanle1, NULL)){
        printf("thread1 error number: %d \n", ret);
        return -1;
    }
    sleep(1);
    if(ret = pthread_create(&thread_id2, NULL, &thr_hanle1, &data)){
        printf("thread2 error number: %d \n", ret);
        return -1;
    }

    sleep(5);
    /**gui yeu cau ket thuc thread cu the*/ 
    pthread_cancel(thread_id2);

    /*doi thread duoc chi finh ket thuc*/
    pthread_join(thread_id2, NULL);

    printf("thread2 termination\n");
}
//////////////////////////////////////////////////////////////

/*pthread_detach 
ket thuc thread tu dong
khong lam cham chuong trinh khi xu ly nhieu thuat toan*
truyen id cua ham can ket thuc bang pthread_self() */
static void *thr_hanler2(void *args) {

    int a = pthread_detach(pthread_self());
    // printf("ket thuc thread, status = %d \n", a);
    // sleep(1);
}

void ngan_zombie(){
    int ret = 0;
    int coun = 0;

    pthread_t thread_id3;

    while(1) {
        if(ret = pthread_create(&thread_id3, NULL, &thr_hanler2, NULL)) {
            printf("pthread3 create( error number = %d \n)", ret);
        }
        /* doi thread ket thuc de ngan tao thread zombie*/
    //    pthread_join(thread_id3, NULL);
        coun++;
        if(coun % 1000 == 0){
            printf(" thread created: %d \n", coun);
        }
    }
}

////////////////////////////////////////////////////////

static void *thr_hanler3(void *args) {
    pthread_mutex_lock(&lock);
    printf("thread3 handler, counter: %d \n", counter++);
    sleep(5);
    pthread_mutex_unlock(&lock);
    int a = pthread_detach(pthread_self());
} 

static void *thr_hanler4(void *args) {
    pthread_mutex_lock(&lock);
    printf("thread4 handler, counter: %d \n", counter++);
    sleep(5);
    pthread_mutex_unlock(&lock);
    int a = pthread_detach(pthread_self());
} 

int thread_lock(){
    int ret = 0;
    if(ret = pthread_create(&thread_id4, NULL, &thr_hanler3, NULL)){
        printf("thread1 error number: %d \n", ret);
        return -1;
    }

    if(ret = pthread_create(&thread_id5, NULL, &thr_hanler4, NULL)){
        printf("thread1 error number: %d \n", ret);
        return -1;
    }
    sleep(2);
}

///////////////////////////////////////////////////////////
