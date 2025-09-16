# Quectel EXTSDK Examples

This part shows how to test the examples in ql-ol-extsdk.

run the script to enable the cross compile tool.

```sh
source ql-ol-crosstool/ql-ol-crosstool-env-init
QUECTEL_PROJECT_NAME      =EC25E
QUECTEL_PROJECT_REV       =EC25EFAR06A12M4G_OCPU_20.200
```

## Linux UserSpace APP

hello.c

```c
#include <stdio.h>
int main()
{
    printf("hello world\n");
    return 0;
}
```

Makefile

```bash
default:
    arm-oe-linux-gnueabi-gcc hello.c -o hello
```

## Linux kernel modules

hello.c

```c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Test");
MODULE_VERSION("V1");
MODULE_DESCRIPTION("Kernel example");

static int year = 2021;

static int __init hello_init(void)
{
    printk(KERN_WARNING "Hello Kernel, it's %d!\n", year);
    return 0;
}

static void __exit hello_exit(void)
{
    printk("Bye, kernel!\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

Makefile

.. highlight:: c

```
obj-m := hello.o
all:
$(MAKE) ARCH=arm CROSS_COMPILE=arm-oe-linux-gnueabi- -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
```

## ql-ol-extsdk
