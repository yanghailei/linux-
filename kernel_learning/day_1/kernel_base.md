# 基础内核模块

本文的目的在与编译出一个可以在Ubuntu上运行的内核模块，hello.ko

# 环境
系统：Ubuntu16.04
编辑器：VSCode
VScode不仅可以编辑代码，还集成了终端。
终端打开方式为 （Ctrl+`） 。这个 “`” 位于Tab上方
make版本：GNU Make 4.1
make版本自带与Ubuntu系统，不用在意make版本，各版本的区别不会影响我们的学习。
```
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ uname -v
#46~16.04.1-Ubuntu SMP Fri Dec 7 13:31:08 UTC 2018
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ make --v
GNU Make 4.1
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```
# 提示
- 编译的内核模块基于Ubuntu系统内核，因此不需要额外的内核代码或编译器，均使用系统自带。
- 加载内核命令为 insmod modulename
- 卸载内核模块命令为 rmmod modulename
- 经测试，作者使用的Ubuntu并不识别makefile，应改为Makefile
- 在编译时可能提示需要libelf-dev库，安装即可编译通过

# 代码部分
### 建立helloc.c 文件，内容如下：
```
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk(KERN_INFO "Run the hello_init \n");
    return 0;
}
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Run the hello_exit \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL v2");
```
### 建立Makefile文件，内容如下。
```
KER_VER = $(shell uname -r)
obj-m += hello.o
build:kernel_modules
kernel_modules:
	make -C /lib/modules/$(KER_VER)/build M=$(CURDIR) modules
clean:
	make -C /lib/modules/$(KER_VER)/build M=$(CURDIR) clean
```
# 代码解释
在hello.c文件的 __init 修饰表示这个函数只在初始化时存在，初始化完成即销毁。__exit表示如果模块不是动态加载而是直接编译进内核的话，_exit修饰的函数将会被省略，结果就是这个模块不能被卸载。
MODULE_LICENSE("GPL v2");用来声明模块是开源的，没有这句话，编译内核时会有警告。

# 编译演示
执行下面的命令，可以看到编译成功，并且产生了我们需要的hello.ko模块。
```
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ ls
hello.c  Makefile
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ make
make -C /lib/modules/4.15.0-43-generic/build M=/home/hailei/linux-learning/kernel_learning/day_1/code modules
make[1]: Entering directory '/usr/src/linux-headers-4.15.0-43-generic'
  CC [M]  /home/hailei/linux-learning/kernel_learning/day_1/code/hello.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/hailei/linux-learning/kernel_learning/day_1/code/hello.mod.o
  LD [M]  /home/hailei/linux-learning/kernel_learning/day_1/code/hello.ko
make[1]: Leaving directory '/usr/src/linux-headers-4.15.0-43-generic'
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ ls
hello.c   hello.mod.c  hello.o   modules.order
hello.ko  hello.mod.o  Makefile  Module.symvers
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$
```
# 模块的加载与卸载
模块加载时，根据我们的程序，应当输出Run in the hello_init
模块卸载时，应当输出Run in the hello_exit
执行加载与卸载命令后，没有发现输出，是因为我们用的输出时printk函数，函数输出的内容在内核。
在终端内输入dmesg可以看到输出。具体如下。
```
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ sudo insmod hello.ko
[sudo] hailei 的密码：
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ sudo rmmod hello.ko
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$ dmesg

[34851.502497] Run the hello_init
[34859.905624] Run the hello_exit
>hailei@hailei-Lenovo-G470:~/linux-learning/kernel_learning/day_1/code$
```