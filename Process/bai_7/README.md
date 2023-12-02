Makefile
    .PHONY: all clean
all:
	gcc -o process_sig main.c
clean:
	rm -rf process_sig

+ Code:
	su dung SIGCHLD de ngan ngua hinh thanh zombie process