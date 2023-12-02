#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int fd = 0;
int w = 0;

/*lệnh lseek SEEL_SET đưa con trỏ phần đầu file 
nhưng nếu không có flag O_APPEND thì con trỏ 
vẫn ở cuối file dù chúng ta đã set SEEK_SET
*/
int main(){
    char *text = "text.txt";
    char buff[] = {"hello word"};
    
    fd = open(text, O_RDWR | O_APPEND);
    if(fd == -1){
        printf("open error\r\n");
    }

    lseek(fd, 20, SEEK_SET);
    w = write(fd, buff, strlen(buff));
    if(w == -1){
        printf("write error \r\n");
    }
}
