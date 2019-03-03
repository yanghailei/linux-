

KER_VER = $(shell uname -r)

obj-m += hello.o

build:kernel_modules

kernel_modules:
	make -C /lib/modules/$(KER_VER)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KER_VER)/build M=$(CURDIR) clean