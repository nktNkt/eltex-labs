obj-m += kspace.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o uspace uspace.c


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm uspace
