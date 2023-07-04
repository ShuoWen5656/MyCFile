//
// Created by 赵烁文 on 2023/7/1.
//
/**
 * 题目：设计一个有getMin功能的栈
 */

#include "min_stack.h"
#include <stdlib.h>

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif


/**
* 初始化一个minstack类型
* @return
*/
MinStack* min_stack_init() {
    // 初始化当前对象指针
    MinStack* minStack = calloc(1, sizeof(MinStack));
    // 初始化成员变量
    minStack->stack = stack_init();
    minStack->minStack = stack_init();
    return minStack;
}

/**
* 入栈一个元素
* @param minStack
* @param data
*/
void min_stack_push(MinStack* minStack, void* data) {
    // 取值
    int cur = *(int*)data;
    Stack* stack = minStack->stack;
    Stack* mStack = minStack->minStack;
    if (stack_is_empty(stack)) {
        // 先正常入栈
        stack_push(stack, data);
        stack_push(mStack, data);
    }else {
        // 先正常入栈
        stack_push(stack, data);
        int peek = stack_peek(mStack);
        if (cur < peek) {
            // 入栈
            stack_push(stack, data);
        }
    }
}


/**
 * 出栈一个元素
 * @param minStack
 * @return
 */
int min_stack_poll(MinStack* minStack) {
    Stack* stack = minStack->stack;
    Stack* m_stack = minStack->minStack;
    if (stack == NULL) {
        return 0;
    }
    int pool = *(int*)stack_poll(stack);
    int m_peek = *(int*)stack_peek(m_stack);
    if (m_peek == pool) {
        // 两个堆顶相同时弹出小堆
        stack_poll(m_stack);
    }
    return pool;
}

/**
 * 获取当前栈中的最小值
 * @param minStack
 * @return
 */
int min_stack_get_min(MinStack* minStack) {
    // 获取最小值堆顶即可
    return *(int*) stack_peek(minStack->minStack);
}



/**
 * 测试用例
 * @return
 */
int main() {
    return 0;
}



#ifdef __cplusplus
};
#endif







