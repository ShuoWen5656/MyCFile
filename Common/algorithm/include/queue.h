//
// Created by 赵烁文 on 2023/7/27.
//

/**
 * 简单队列
 */
#ifndef MYCPROJECT_QUQUE_H
#define MYCPROJECT_QUQUE_H

#endif //MYCPROJECT_QUQUE_H

#include "arraylist.h"

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Queue {
    ArrayList* arrayList;
}Queue;

/**
 * 构造函数
 * @return
 */
Queue* queue_init();

/**
 * push 到队列尾巴
 * @param queue
 */
void queue_push(Queue* queue, void* data);

/**
 * 弹出队头
 * @param quque
 * @return
 */
void* queue_poll(Queue* queue);

/**
 * 查看队头
 * @param quque
 * @return
 */
void* queue_peek(Queue* queue);

/**
 * 判空
 * @param queue
 * @return
 */
int queue_is_empty(Queue* queue);

/**
 * 清空元素，但不释放内存
 * @param queue
 */
void queue_clear(Queue* queue);

/**
 * 清空元素并释放内存
 * @param queue
 */
void queue_free(Queue* queue);

#ifdef __cplusplus
};
#endif