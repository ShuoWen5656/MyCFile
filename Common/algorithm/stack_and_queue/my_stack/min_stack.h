//
// Created by 赵烁文 on 2023/7/1.
//

#ifndef MYCPROJECT_MY_STACK_H
#define MYCPROJECT_MY_STACK_H

#endif //MYCPROJECT_MY_STACK_H

#include "../../data_struct/stack/stack.h"


/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

//能够实时获取最小值的栈结构
typedef struct MinStack {
    /**
     * 正常栈存储
     */
    Stack* stack;
    /**
     * 最小值栈存储
     */
    Stack* minStack;
}MinStack;

/**
 * 初始化一个minstack类型
 * @return
 */
MinStack* min_stack_init();


/**
 * 入栈一个元素
 * @param minStack
 * @param data
 */
void min_stack_push(MinStack* minStack, void* data);


/**
 * 出栈一个元素
 * @param minStack
 * @return
 */
int min_stack_poll(MinStack* minStack);

/**
 * 获取当前栈中的最小值
 * @param minStack
 * @return
 */
int min_stack_get_min(MinStack* minStack);




#ifdef __cplusplus
};
#endif


