# 汇编语言运行命令

1、 汇编操作

as --32  exit.s -o exit.o

2、链接操作

ld -m elf_i386 exit.o -o exit
