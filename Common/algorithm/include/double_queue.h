//
// Created by 赵烁文 on 2023/8/7.
//
/**
 * 双端队列
 */
#ifndef MYCPROJECT_DOUBLE_QUEUE_H
#define MYCPROJECT_DOUBLE_QUEUE_H

#endif //MYCPROJECT_DOUBLE_QUEUE_H

#include "arraylist.h"
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * 双端队列数据结构
 */
typedef struct DoubleQueue{
    ArrayList* arrayList;
}DoubleQueue;

/**
 * 初始化双端队列
 * @return
 */
DoubleQueue* double_queue_init();

/**
 * push一个元素到队尾
 */
void double_queue_push(DoubleQueue* doubleQueue, void* data);

/**
 * poll一个队头的元素
 */
void* double_queue_poll(DoubleQueue* doubleQueue);

/**
 * 查看对头
 */
void* double_queue_peek(DoubleQueue* doubleQueue);

/**
 * 查看对头
 */
int double_queue_is_empty(DoubleQueue* doubleQueue);

/**
 * 查看对头
 */
void* double_queue_peek_first(DoubleQueue* doubleQueue);
/**
 * 查看队尾
 */
void* double_queue_peek_last(DoubleQueue* doubleQueue);
/**
 * 查看队头
 */
void* double_queue_poll_first(DoubleQueue* doubleQueue);

/**
 * 查看队尾
 */
void* double_queue_poll_last(DoubleQueue* doubleQueue);

/**
 * push一个元素到队头
 */
void double_queue_push_first(DoubleQueue* doubleQueue, void* data);

/**
 * push一个元素到队尾
 */
void double_queue_push_last(DoubleQueue* doubleQueue, void* data);

/**
 * 清空元素
 */
void* double_queue_clear(DoubleQueue* doubleQueue);

/**
 * 释放内存
 */
void* double_queue_free(DoubleQueue* doubleQueue);

#ifdef __cplusplus
};
#endif