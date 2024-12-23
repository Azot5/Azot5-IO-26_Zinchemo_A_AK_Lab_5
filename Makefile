
ifneq ($(KERNELRELEASE),)

ccflags-y := -I$(PWD)/inc
obj-m += hello1.o
obj-m += hello2.o
else

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif
