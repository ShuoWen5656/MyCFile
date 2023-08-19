# 目的：获取数组中的最大值
# 变量：寄存器有一下用途
#   %edi - 保存当前被检测到的数据项索引
#   %eax - 当前数据项
#   %ebx - 到目前为止的最大值
# 内存位置：
#   data_items - 包含的数组位置
#                数据0表示数据结束
# 数据段声明需要比较的数据
.section .data
data_items:
 .long 3,6,7,54,34,22,43,0
.section .text
.global _start
_start:
 # 初始化将当前索引设置为第一个索引，值为第一个值，最大值也是第一个值
 movl $0, %edi
 # 从edi开始取4个字节
 movl data_items(, %edi, 4), %eax
 # 当前最大值为ebx
 movl %eax, %ebx

 # 开始循环
start_loop:
  # 先判断是否ax已经到最后一个值了
  cmpl $0, %eax
  # je为相等的意思
  je exit_loop
  # 将下一个值取出来
  incl %edi
  movl data_items(, %edi, 4), %eax
  cmpl %ebx, %eax
  # 如果新的数据项没有大于原来的值，则继续循环
  jle start_loop
  # 否则赋值
  movl %eax, %ebx
  jmp start_loop




# 结束循环
exit_loop:
    # 调用一次系统调用，eax置为1，ebx置为最大值结果（无需变化）
 movl $1, %eax
 int $0x80

