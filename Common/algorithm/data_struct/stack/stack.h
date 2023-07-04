//
// Created by 赵烁文 on 2023/1/15.
//

#ifndef MYCPROJECT_STACK_H
#define MYCPROJECT_STACK_H


#include "../arraylist/arraylist.h"
#include "stdbool.h"

#endif //MYCPROJECT_STACK_H
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 类似于java Stack功能
 */

// 栈结构定义,相当于arraylist的一层封装
typedef struct Stack {
    ArrayList* arrayList;
}Stack;


/**
 * 初始化栈结构
 * 相当于new
 * @return
 */
Stack* stack_init();

/**
 * 加入一个元素
 * @param stack
 * @param p_data
 * @return
 */
int stack_push(Stack* stack, void* p_data);

/**
 * 弹出一个元素
 * @param stack
 * @return
 */
void* stack_poll(Stack* stack);

/**
 * 判断栈是否为空
 * @param stack
 * @return
 */
int stack_is_empty(Stack* stack);

/**
 * 获取栈顶元素
 * @param stack
 * @return
 */
void* stack_peek(Stack* stack);

/**
 * 清空栈
 * @param stack
 */
void stack_clear(Stack* stack);

/**
 * 释放栈内存
 * @param stack
 */
void stack_free(Stack* stack);














#ifdef __cplusplus
};
#endif
