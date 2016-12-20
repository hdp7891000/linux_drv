# Makefile2.6
ifneq ($(KERNELRELEASE),)
#kbuild syntax. dependency relationshsip of files and target modules are listed here.
	obj-m := char_null_udev.o
else
	PWD := $(shell pwd)
	KVER = 2.6.35.3
	KDIR := ~/linuxksrc/linux-2.6.35.3
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order
endif
