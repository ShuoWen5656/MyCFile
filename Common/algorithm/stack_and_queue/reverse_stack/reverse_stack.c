//
// Created by 赵烁文 on 2023/7/23.
//


/**
 * 问题：如何仅用递归函数和栈操作逆序一个栈
 */

#include <stdio.h>
#include "stack.h"

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
* 递归函数主体
*/
void process1(Stack* stack);
/**
* 递归函数副主体
*/
int* process2(Stack* stack);

/**
* 递归函数副主体(另一种判断方法)
*/
int* process3(Stack* stack);

/**
 * 主函数
 * @return
 */
//int main() {
//    // 创建一个栈
//    Stack* stack = stack_init();
//    int nums[] = {0,1,2,3,4,5};
//    for (int i = 0; i < 6; ++i) {
//        stack_push(stack, &nums[i]);
//    }
//    process1(stack);
//    for (int i = 0; i < 6; ++i) {
//        printf("The first num is : %d \n", *(int*)stack_poll(stack));
//    }
//    stack_free(stack);
//    return 0;
//}


/**
 * 1、通过process2将最下面的取出来，但不放入
 * 2、进行下一次process1递归
 * 3、然后再放入当前层取到的值
 * @param stack
 */
void process1(Stack* stack){
    if (stack_is_empty(stack)) {
        return;
    }
    // 取stack最底层的值的地址，其实用值也可以，这里保证原值原地址
    int* p_cur_int = process2(stack);
    // 再取底层
    process1(stack);
    // 放入
    stack_push(stack, p_cur_int);
}

/**
 * 1、先取
 * 2、判断是否已经空，如果是空说明取的是底层，直接返回,否则继续递归
 * @param stack
 * @return
 */
int* process2(Stack* stack){
    if (stack_is_empty(stack)) {
        return 0;
    }
    // 获取当前层的值
    int* p_cur = stack_poll(stack);
    // 继续获取底
    int* next = process2(stack);
    if (next == 0) {
        // 说明当前就是底层了
        return p_cur;
    }else {
        // 将自己重新放回栈，返回底层
        stack_push(stack, p_cur);
        return next;
    }
}

int* process3(Stack* stack) {
    if (stack_is_empty(stack)) {
        return 0;
    }
    // 获取当前层的值
    int* p_cur = stack_poll(stack);
    // 直接判断是不是空
    if (stack_is_empty(stack)) {
        return p_cur;
    }else {
        // 将自己先放回去
        stack_push(stack, p_cur);
        // 还有值就继续取
        return process3(stack);
    }
}


#ifdef __cplusplus
};
#endif



