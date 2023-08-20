//
// Created by 赵烁文 on 2023/8/13.
//

#include <stdlib.h>
#include <stdio.h>
#include "double_queue.h"
/***************************************************
 *          该文件为头文件double_queue.h的方法实现  *
 ***************************************************/


/**
 * 初始化双端队列
 * @return
 */
DoubleQueue* double_queue_init(){
    DoubleQueue* doubleQueue = calloc(1, sizeof(DoubleQueue));
    doubleQueue->arrayList = init_array_list();
    return doubleQueue;
}

/**
 * push一个元素到队尾
 */
void double_queue_push(DoubleQueue* doubleQueue, void* data) {
    if (doubleQueue == NULL) {
        return;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    // 加到队尾即可
    array_list_insert(arrayList, data, -1);
}

/**
 * poll一个队头的元素
 */
void* double_queue_poll(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_remove_at(arrayList, 0);
}

/**
 * 查看对头
 */
void* double_queue_peek(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_get(arrayList, 0);
}

/**
 * 判空
 */
int double_queue_is_empty(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_is_empty(arrayList);
}

/**
 * 查看对头
 */
void* double_queue_peek_first(DoubleQueue* doubleQueue){
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_get(arrayList, 0);
}
/**
 * 查看队尾
 */
void* double_queue_peek_last(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_get(arrayList, -1);
}
/**
 * 弹出队头
 */
void* double_queue_poll_first(DoubleQueue* doubleQueue) {
    return double_queue_poll(doubleQueue);
}

/**
 * 弹出队尾
 */
void* double_queue_poll_last(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return NULL;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    return array_list_remove_at(arrayList, -1);
}

/**
 * push一个元素到队头
 */
void double_queue_push_first(DoubleQueue* doubleQueue, void* data) {
    if (doubleQueue == NULL) {
        return;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    array_list_insert(arrayList, data, 0);
}

/**
 * push一个元素到队尾
 */
void double_queue_push_last(DoubleQueue* doubleQueue, void* data) {
    double_queue_push(doubleQueue, data);
}


/**
 * 清空元素
 */
void double_queue_clear(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    array_list_clear(arrayList);
}

/**
 * 释放内存
 */
void double_queue_free(DoubleQueue* doubleQueue) {
    if (doubleQueue == NULL) {
        return;
    }
    ArrayList* arrayList = doubleQueue->arrayList;
    array_list_free(arrayList);
    free(doubleQueue);
}


/**
 * 测试用例
 * @return
 */
//int main() {
//    setbuf(stdout, NULL);
//    DoubleQueue* doubleQueue = double_queue_init();
//    int len = 4;
//    int* ints = calloc(len, sizeof(int));
//    for (int i = 0; i < len; ++i) {
//        ints[i] = i;
//    }
//    double_queue_push_first(doubleQueue, &ints[0]);
//    double_queue_push_last(doubleQueue, &ints[1]);
//    double_queue_push(doubleQueue, &ints[2]);
//    double_queue_push_first(doubleQueue, &ints[3]);
//    ArrayList* arrayList = doubleQueue->arrayList;
//    for (int j = 0; j < len; ++j) {
//        printf("the index %d is %d \n", j, *(int*)array_list_get(arrayList, j));
//    }
//    // 测试读
//    int i1 = *(int*)double_queue_peek(doubleQueue);
//    int i2 = *(int*)double_queue_peek_last(doubleQueue);
//    int i3 = *(int*)double_queue_poll_first(doubleQueue);
//    int i4 = *(int*)double_queue_poll_last(doubleQueue);
//
//    double_queue_free(doubleQueue);
//    return 0;
//}





