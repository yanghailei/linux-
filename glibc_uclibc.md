# uClibc 和 uClibc

uClinux的通用c库:uC-libc和uClibc的区别概述uClinux通常使用两种c库:uC-libc和uClibc.尽管它们名字近似,但有很大区别.本文是对它们不同点的快速浏览.
uC-libc是uClinux的原始c 库,它基于Linux-8086 c库,该c 库是ELKs 工程的一部分,支持m68000结构.uC-libc是一个相当全面的c 库,但它的一些API是非标准的,一些通用库例程现在已不再使用.目前它能稳定地支持m68000,ColdFire和ARM(不带MMU)结构 .其主要设计目标是小型化和轻量级.它力图符合通用标准,它的API也与绝大多数的c 库兼容,但与标准难免有出入.
uClibc是uC-libc的派生体,用来解决uC-libc存在的问题.它让所有的API都标准化(正确的类型,参数等),补充了许多缺失的例程,并且已经移植到许多结构中.大体上讲,它通过提供glibc兼容使得应用程序移植到较小的c 库时相当得容易. 它能够应用到带虚拟存储的Linux和uClinux上.在大多数带MMU部件的平台上为使它更加紧凑,它也能够编译成共享库.uClibc支持许多处理器:m68000,ColdFire,ARM,MIPS,v850,x86,i960,Sparc,SuperH,Alpha,PowerPC和 Hitachi 8.uClibc能更加容易地适应新的体系结构,它所支持的平台数目至今仍在增长证实了这一点.
可以根据你的需要来选择uClinux使用uC-libc或者uClibc编译环境.对m68000和ColdFire平台通常选择uC-libc, 因为它支持共享库,是这些处理器上使用最广泛的c 库.uClibc also works quite well with almost all platforms supported by the distribution.你的需要将最终决定到底选择哪一种c库.


# glibc
GCC的标准库，就是glibc这个库，里面有GCC各种标准函数的实现，还有各种unix系的函数在里面。当初创建uclinux的时候，需要一个能编译比较小体积的目标文件的便宜器，这个时候就有人写了一个uc-libc库，这个库可以说是uclinux上的一个glibc移植，但是还是有很多函数没有实现，所以人们只能勉强用它来在uclinux上写程序。后来，有牛人又写了uclibc,这个是真正意义上的瘦身过后的glibc,完成了很多以前uc-libc不支持的函数。本人觉得最有价值的就是uclibc实现了pthread系列函数，以前用uc-libc只能用fork+exec来完成的多线程功能。uclibc现在也不只是用在嵌入式系统上面，一些人也喜欢在标准平台使用它来编译一些程序。

uC-libc是早期版本，不要考虑了，除非你想考古。
uClibc支持动态连接，但我认为目前uClibc的优势还是在静态连接上。比glibc自然小很多，是否选择uClibc因素很多，比如看你的文件系统大小，如果超过20M，用glibc更简单，glibc已经久经考验了；如果小于4M，可以考虑用uClibc，体积小是很大的优势。