//
// Created by 赵烁文 on 2023/7/27.
//

/**
 * 问题：猫狗队列
 */

#include "cat_dog_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 猫狗队列初始化
 * @return
 */
CatDogQueue* cat_dog_queue_init() {
    CatDogQueue* catDogQueue = NULL;
    catDogQueue = calloc(1, sizeof(CatDogQueue));
    catDogQueue->dogQueue = queue_init();
    catDogQueue->catQueue = queue_init();
    catDogQueue->time = 0;
}

/**
 * 队列push操作
 * @param queue
 * @param data
 */
void cat_dog_queue_push(CatDogQueue* queue, CatOrDog* data) {
    if (queue == NULL || data == NULL) {
        return;
    }
    Queue* catQueue = queue->catQueue;
    Queue* dogQueue = queue->dogQueue;
    // 设置time
    data->time = queue->time++;
    if (data->type == 0) {
        // 猫队列
        queue_push(catQueue, data);
    }else if (data->type == 1) {
        queue_push(dogQueue, data);
    }
}

/**
 * 正常队列弹出
 * 两队头谁小谁出去
 * @param queue
 * @return
 */
void* cat_dog_queue_poll(CatDogQueue* queue) {
    if (cat_dog_queue_is_empty(queue)) {
        return NULL;
    }
    // 肯定有一个队列不是空
    Queue* catQueue = queue->catQueue;
    Queue* dogQueue = queue->dogQueue;
    CatOrDog* cat_peek = (CatOrDog*)queue_peek(catQueue);
    CatOrDog* dog_peek = (CatOrDog*)queue_peek(dogQueue);
    if (cat_peek == NULL) {
        return queue_poll(dogQueue);
    }
    if (dog_peek == NULL) {
        return queue_poll(catQueue);
    }
    return cat_peek->time < dog_peek->time ? queue_poll(catQueue) : queue_poll(dogQueue);
}

/**
 * 只弹出一只cat
 * @param queue
 * @return
 */
void* cat_dog_queue_poll_cat(CatDogQueue* queue) {
    if (cat_dog_queue_is_empty(queue)) {
        return NULL;
    }
    Queue* catQueue = queue->catQueue;
    return queue_is_empty(catQueue) ? NULL : queue_poll(catQueue);
}

/**
 * 只弹出一只dog
 * @param queue
 * @return
 */
void* cat_dog_queue_poll_dog(CatDogQueue* queue) {
    if (cat_dog_queue_is_empty(queue)) {
        return NULL;
    }
    Queue* dogQueue = queue->dogQueue;
    return queue_is_empty(dogQueue) ? NULL : queue_poll(dogQueue);
}

/**
 * 判断队列是否空
 * @param queue
 * @return
 */
int cat_dog_queue_is_empty(CatDogQueue* queue) {
    if (queue == NULL) {
        return 1;
    }
    Queue* catQueue = queue->catQueue;
    Queue* dogQueue = queue->dogQueue;
    if (queue_is_empty(catQueue) && queue_is_empty(dogQueue)) {
        return 1;
    }
    return 0;
}

/**
 * 清空队列
 * @param queue
 */
void cat_dog_queue_clear(CatDogQueue* queue) {
    if (queue == NULL) {
        return;
    }
    Queue* catQueue = queue->catQueue;
    Queue* dogQueue = queue->dogQueue;
    queue_clear(catQueue);
    queue_clear(dogQueue);
}

/**
 * 释放队列内存
 * @param queue
 */
void cat_dog_queue_free(CatDogQueue* queue) {
    if (queue == NULL) {
        return;
    }
    Queue* catQueue = queue->catQueue;
    Queue* dogQueue = queue->dogQueue;
    if (catQueue != NULL){
        queue_free(catQueue);
    }
    if (dogQueue != NULL) {
        queue_free(dogQueue);
    }
}



/**
 * 测试用例
 * @return
 */
//int main() {
//    // 创建一个队列
//    CatDogQueue* catDogQueue = cat_dog_queue_init();
//    CatOrDog* catsOrDogs = calloc(10, sizeof(CatOrDog));
//    srand(time(0));
//    for (int i = 0; i < 10; i++) {
//        // 奇数为狗,偶数为猫
//        catsOrDogs[i].type = (rand() & 1);
//        // 放入队列
//        cat_dog_queue_push(catDogQueue, &catsOrDogs[i]);
//    }
//    // 开始弹出
//    CatOrDog* dog = cat_dog_queue_poll_dog(catDogQueue);
//    CatOrDog* cat = cat_dog_queue_poll_cat(catDogQueue);
//    // 随便弹出一个
//    CatOrDog* tail = cat_dog_queue_poll(catDogQueue);
//    // 测试empty
//    int is_empty = cat_dog_queue_is_empty(catDogQueue);
//    cat_dog_queue_free(catDogQueue);
//    free(catsOrDogs);
//}

#ifdef __cplusplus
};
#endif
