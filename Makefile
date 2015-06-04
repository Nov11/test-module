ifneq ($(KERNELRELEASE),)
	obj-m += cdev.o
else
default:
	make -C /lib/modules/3.17.4-301.fc21.x86_64/build/ M=`pwd`
.PHONY:clean
clean:
	make -C /lib/modules/3.17.4-301.fc21.x86_64/build/ M=`pwd` clean
endif
