## C语言项目
该项目为c语言项目，其中包括各类算法的c语言实现
-- c语言执行分为4步：
1、预处理：主要将include文件代码集中到本文件中,输出hello.i中间文件
命令：gcc -E hello.c -o hello.i
2、生成编译文件
命令：gcc -S hello.i -o hello.s
3、编译：将编译文件编译成目标文件
命令：gcc -c hello.s -o hello.o
4、链接：将目标文件转为当前架构平台能够执行的文件，如exe等
命令：gcc hello.o -o hello.exe
linux下 gcc hello.o -o hello



