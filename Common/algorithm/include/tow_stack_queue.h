//
// Created by 赵烁文 on 2023/7/22.
//
/**
 * 题目：由两个栈组成的队列
 */
#ifndef MYCPROJECT_TOW_STACK_QUEUE_H
#define MYCPROJECT_TOW_STACK_QUEUE_H

#endif //MYCPROJECT_TOW_STACK_QUEUE_H

#include "stack.h"

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TowStackQueue{
    // 用来进的stack
    Stack* stackIn;
    // 用来弹出的stack
    Stack* stackOut;
    // 当前队列中元素剩余的个数
    int size;
}TowStackQueue;



/**
 * 加入队头
 * @param towStackQueue
 * @param data
 */
void tow_stack_queue_add(TowStackQueue* towStackQueue, void* data);

/**
 * 从队尾弹出
 * @param towStackQueue
 * @return
 */
void* tow_stack_queue_poll(TowStackQueue* towStackQueue);

/**
 * 查看当前队头
 * @param towStackQueue
 * @return
 */
void* tow_stack_queue_peek(TowStackQueue* towStackQueue);

/**
 * 清空所有元素
 * @param towStackQueue
 */
void tow_stack_queue_clear(TowStackQueue* towStackQueue);

/**
 * 释放所有元素的内存
 * @param towStackQueue
 */
void tow_stack_queue_free(TowStackQueue* towStackQueue);

#ifdef __cplusplus
};
#endif
