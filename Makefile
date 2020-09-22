# SPDX-License-Identifier: GPL-2.0-only

obj-m += msr-census.o

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm -f *.ko *.mod *.mod.c *.o *.order *.symvers

