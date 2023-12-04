.PHONY: ALL clean

all:
	gcc main.c -o hello

clean:
	rm -rf test.txt

+ Code

    to file test.txt, ghi mot doan du lieu bat ky
    ghi ra man hinh cac thong in: loai file, ten file,
    thoi gian chinh sua file lan cuoi, kich thuoc (used struct stat)