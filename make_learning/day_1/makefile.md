
# 学习makefile


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
# makefile 介绍
在我们执行make命令时，编译系统会在当前目录下寻找makefile或Makefile的文件，如果同时存在makefile或Makefile，不同编译器有不同的优先选择。makefile或Makefile告诉了编译系统如何生成目标程序。
系统在makefile文件内找到第一个目标或者标签，就会认为第一个目标或者标签就是此次执行的目的，此时文件的第二个，第三个，。。目标或者标签都不会被执行，除非他们和第一个目标有依赖关系。
# makefile 规则
nakefile的规则很简单，就是目标找依赖，找到依赖然后执行命令。找不到依赖就报错。
目标位于一行的开始，目标和依赖之间以“：”分割，命令以一个或多个tab开始。为了规范我们均以一个tab开始
```
目标1 目标2 ... : 依赖1 依赖2 ...
	命令1
	命令2
	...

标签：
	命令1
	命令2
	...
```
举个例子，我们有一个文件first_file.c，内容如下：
```
// first_file.c

#include "stdio.h"

int main(int argc, char *argv)
{
    printf("in first file\n");
    return 0;
}
```
我们在与first_file.c 同级目录下新建一个makefile文件。文件内容如下：
```
# makefile 文件

mytarget:first_file.o
	gcc -o mytarget first_file.o


first_file.o:first_file.c
	gcc -c first_file.c

clean:
	rm *.o mytarget
```
我们来测试一下效果。打开VScode，建立make_learning目录，建立first_file.c makefile ，两个文件，将上述内容拷贝进文件，保存后按下 (Ctr+`)打开终端，输入make，可以看到生成了mytarget文件。执行mytarget，看到输出结果。
```
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ ls
first_file.c  makefile
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ make
gcc -c first_file.c
gcc -o mytarget first_file.o
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ ls
first_file.c  first_file.o  makefile  mytarget
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ ./mytarget
in first file
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$
```
# 例子解释
在上面的makefile 中我们写了三块指令。生成了mytarget 和first_file.o文件
以mytarget开头的一块，表示我们要生成mytarget文件，其需要first_file.o文件
以first_file.o开始的一块表示我们要生成first_file.o文件，需要first_file.c文件
以clean开头的一块表示，我们要执行rm 清除first_file.o mytarget 两个文件
那么对于makefile的解释可以是：
makefile执行时，根据第一个目标，找寻第一个目标的依赖。然后看看第一个目标的依赖文件在哪里，如果没有依赖文件就看看有没有方式能生成依赖文件，然后就不断递归地寻找依赖，直至可以找到最底层的依赖文件。
该例子内的最底层文件就是first_file.c文件，需要first_file.c的就是以first_file.o开始的那块命令，这是一个依赖存在的命令块，依赖存在时就开始执行gcc -c first_file.c，这一步会生成first_file.o文件，.o文件生成后，mytarget的依赖就有了，那么mytarget下面的gcc -o mytarget first_file.o命令就可以执行了。该命令的执行结果就是生成mytarget可执行文件。

# 关于clean
clean没有依赖，在makefile文件内，没有依赖的统称标签，标签的作用就是执行标签以开始的命令块。
这里一定要记住是这个命令块，只是执行到这个命令块结束，不是到文件的结束。我们可以验证，将makefile更改如下：
```
# makefile 文件

mytarget:first_file.o
	gcc -o mytarget first_file.o
	
clean:
	rm *.o mytarget

first_file.o:first_file.c
	gcc -c first_file.c
```

执行过程如下，发现并未生成first_file.o文件。

```
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ ls
first_file.c  first_file.o  makefile  mytarget
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ make clean
rm *.o mytarget
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$ ls
first_file.c  makefile
>hailei@hailei-Lenovo-G470:~/linux-learning/make_learning$
```


## 注意
- Makefile 与makefile的功能是一样的，只是不同系统要求的名字不同。系统一般会允许程序员自由决定使用哪一个，只是两个文件同时存在是系统有自己的优先选择权。
- 在测试环境内，我们是在linux系统环境下编程，一个可执行程序只有一个main函数，且必须是int main(int argc, char *argv)的形式，执行结束应返回值0。
- 执行可执行程序时执行方式为 ./程序名称， 直接在命令行中输入名字，系统会提示找不到文件。具体原因请百度。
- makefile隐含的推导规则过于复杂，作者尚不能解释清楚。具体就是可以省略很多命令，由系统自动推导出需要的命令及找到自己需要的文件或生成自己需要的文件。
- 在例子中first_file.c内需要了头文件，我们在makefile内并未指出first_file.o依赖该头文件，因为GCC编译器包含了头文件。如果是我们自己的头文件，一定要指出我们自己的头文件。