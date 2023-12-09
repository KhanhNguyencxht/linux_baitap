    Viết một chương trình thực hiện tạo 2 threads. Cả hai threads này đều dùng chung một handler:
        + Kiểm tra nếu là thread1 đang thực hiện thì in ra thông điệp bất kì để xác định. 
        + Nếu là thread2 thì truyền vào dữ liệu kiểu struct human được khởi tạo từ trước, với các thông tin: Họ tên, năm sinh, sdt, quê quán. Sau đó in các thông tin này ra màn hình
    
    Makefile:
        + make all chay main.c tao file exam11
        + make clear: xoa file exam11
    Code:
        + thread_create tao thr_hanle1
        + ngan_zombie tao thr_hanler2
        + thread_lock tao thr_hanler3, thr_hanler4