
CC = arm-none-linux-gnueabi-gcc

all:
	make -C ../src
	$(CC) show.c -o show -L ../src/ -ldev
	$(CC) led_wtd_demo.c -o led_wtd_demo -L ../src/ -ldev

clean:
	rm show  led_wtd_demo
	make clean -C ../src

