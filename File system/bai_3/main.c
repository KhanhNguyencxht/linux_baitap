// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <time.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <libgen.h>
#include <time.h>
#include <unistd.h>

char *file_name = "test.txt";
char *data = "hello word! \r\n";

int fd = 0;
ssize_t value = 0;
// take informatinon file


int main(){
struct stat information_file;

    fd = open(file_name, O_CREAT | O_RDWR);
    if(-1 == fd){
        printf("open creat err\r\n");
//        exit(1);
    }

    value = write(fd, data, strlen(data));
    if(-1 == value){
        printf("write error \r\n");
//        exit(1);
    }
    if(-1 == stat(file_name, &information_file)){
        printf("information_file error \r\n");
//        exit(1);
    }

    printf("type file: ");
    switch (information_file.st_mode & __S_IFMT)
    {
       case __S_IFBLK:
        printf("block device\n");
        break;
        case __S_IFCHR:
        printf("character device\n");
        break;
        case __S_IFDIR:
        printf("directory\n");
        break;
        case __S_IFIFO:
          printf("FIFO/pipe\n");
          break;
        case __S_IFLNK:
        printf("symlink\n");
        break;
        case __S_IFREG:
        printf("regular file\n");
        break;
        case __S_IFSOCK:
        printf("socket\n");
        break;
        default:
        printf("unknown?\n");
        break;
    }

     printf("file name: %s \r\n", file_name);
    // convert time 
    printf("time edit Final: %s \r\n", ctime(&information_file.st_mtime));
    printf("file size: %d \r\n", information_file.st_size);

    value = close(fd);
    if(-1== value){
        printf("close error\r\n");
//        exit(1);
        }
}