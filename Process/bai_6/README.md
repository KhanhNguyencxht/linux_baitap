.PHONY: all clean

all:
	gcc -o process_wait main.c
clean: 
	rm -rf process_wait

+ Code:

    viet chuong trinh A tao ra tien trinh con B
    in ra PID, PPID cua chuong
    su dung system waitpid() de lay duoc trang thai ket thuc tien trinh con B
