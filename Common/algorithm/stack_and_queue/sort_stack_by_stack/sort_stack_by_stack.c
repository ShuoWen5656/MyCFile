//
// Created by 赵烁文 on 2023/7/30.
//
/**
 * 问题：用一个栈实现另一个栈的排序
 */

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#include <stdlib.h>
#include "stack.h"
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************
 *          函数签名           *
 *****************************/
/**
 * 使用辅助栈实现当前栈的排序
 * @param stack
 */
void sort_stack_by_stack(Stack* stack);
/**
 * 递归主体
 * @param stack
 * @param help
 */
void sort_stack_by_stack_process(Stack *stack, Stack *help);

/**
 * 找到pint的归宿
 * @param pStack
 * @param pInt
 */
void sort_stack_by_stack_process2(Stack *stack, int *p_cur);




void sort_stack_by_stack(Stack* stack) {
    // 构造辅助栈
    Stack* help = stack_init();
    // 先将所有数据都放入help 中
    while (!stack_is_empty(stack)) {
        stack_push(help, stack_poll(stack));
    }
    sort_stack_by_stack_process(stack, help);
}

void sort_stack_by_stack_process(Stack *stack, Stack *help) {
    if (stack_is_empty(help)){
        return;
    }
    // 先弹出栈顶
    int* cur = (int*)stack_poll(help);
    // 默认stack从顶到底是从小到大，那么找到stack中刚好大于cur的值,将cur放入即可
    sort_stack_by_stack_process2(stack, cur);
    sort_stack_by_stack_process(stack, help);
}

void sort_stack_by_stack_process2(Stack *stack, int *p_cur) {
    if (stack_is_empty(stack) ||  (*p_cur) <= (*(int*)stack_peek(stack))) {
        stack_push(stack, p_cur);
    }else {
        // 比栈顶大，弹出当前值，交给下一层完成之后再将自己放回去
        int* cur2 = stack_poll(stack);
        sort_stack_by_stack_process2(stack, p_cur);
        stack_push(stack, cur2);
    }
}

/**
 * 测试用例
 * @return
 */
//int main() {
//    Stack* stack = stack_init();
//    // 准备数据
//    int ints[] = {1,5,2,3,4};
//    for (int i = 0 ; i < 5; i++) {
//        stack_push(stack, &ints[i]);
//    }
//    sort_stack_by_stack(stack);
//}


#ifdef __cplusplus
};
#endif