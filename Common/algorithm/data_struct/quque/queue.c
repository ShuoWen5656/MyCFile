//
// Created by 赵烁文 on 2023/7/27.
//

/***************************************************
 *          该文件为头文件Queue.h的方法实现            *
 ***************************************************/


/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#include "queue.h"
#include <stdlib.h>


/**
* 构造函数
* @return
*/
Queue* queue_init() {
    Queue* queue = NULL;
    queue = calloc(1, sizeof(Queue));
    queue->arrayList = init_array_list();
}


/**
* push 到队列尾巴
* @param queue
*/
void queue_push(Queue* queue, void* data) {
    if (queue == NULL) {
        return;
    }
    ArrayList* arrayList = queue->arrayList;
    array_list_insert(arrayList, data, -1);
}

/**
 * 弹出队头
 * @param quque
 * @return
 */
void* queue_poll(Queue* queue) {
    if (queue == NULL || queue->arrayList == NULL || queue->arrayList->len == 0) {
        return NULL;
    }
    return array_list_remove_at(queue->arrayList, 0);
}

/**
 * 弹出队头
 * @param quque
 * @return
 */
void* queue_peek(Queue* queue) {
    if (queue == NULL || queue->arrayList == NULL || queue->arrayList->len == 0) {
        return NULL;
    }
    return array_list_get(queue->arrayList, 0);
}

/**
 * 判空
 * @param queue
 * @return
 */
int queue_is_empty(Queue* queue) {
    if (queue == NULL || queue->arrayList == NULL || queue->arrayList->len == 0) {
        return 1;
    }else {
        return 0;
    }
}



/**
 * 清空元素，但不释放内存
 * @param queue
 */
void queue_clear(Queue* queue) {
    array_list_clear(queue->arrayList);
}

/**
 * 清空元素并释放内存
 * @param queue
 */
void queue_free(Queue* queue) {
    if (queue == NULL) {
        return;
    }
    if (queue->arrayList != NULL) {
        array_list_free(queue->arrayList);
    }
    free(queue);
}

#ifdef __cplusplus
};
#endif
