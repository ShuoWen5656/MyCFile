# 目的 退出并向linux内核返回一个状态码的简单程序
#
# 输入 : 无
# 输出 : 返回一个状态码,在运行程序之后可通过echo $? 来进行读取状态

# 变量:
#       %eax 保存系统调用号
#       %ebx保存返回状态码
#
# 数据段,目前程序没有数据段
.section .data
# 文本段，目前也没有文本段
.section .text
# 声明一个全局变量_start 作为程序执行的入口地址
.global _start
_start:
 movl $1, %eax
 movl $0, %ebx
 int $0x80  #系统中断
