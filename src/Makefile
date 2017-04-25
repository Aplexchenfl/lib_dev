CC = arm-none-linux-gnueabi-gcc
AR = arm-none-linux-gnueabi-ar


all:
	$(CC)  lib_dev.c   -fPIC -shared -o libdev.so
	$(CC)  -c lib_dev.c -o libdev.o -I ../include
	$(AR)  rcv libdev.a libdev.o

clean:
	rm *.so *.o *.a

