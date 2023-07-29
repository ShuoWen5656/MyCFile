//
// Created by 赵烁文 on 2023/7/27.
//

#ifndef MYCPROJECT_CAT_DOG_QUQUE_H
#define MYCPROJECT_CAT_DOG_QUQUE_H

#endif //MYCPROJECT_CAT_DOG_QUQUE_H


/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#include "queue.h"
/**
 * 猫对象或者狗对象结构
 * 注：c语言不是面向对象的语言，因此，这里使用了type用来区分，当前结构既可以作为猫，也可以作为狗
 * 猫狗数据大小一致，使用地址表示即可
 */
typedef struct CatOrDog{
    /**
     * 0：cat
     * 1: dog
     */
    int type;

    /**
     * 当前猫/狗的编号
     */
    int time;
}CatOrDog;


/**
 * 猫狗队列数据结构
 */
typedef struct CatDogQueue{
    /**
     * 猫队列
     */
    Queue* catQueue;
    /**
     * 狗队列
     */
    Queue* dogQueue;

    /**
     * 类似于时间戳作为每一个对象进来的标识
     */
    int time;
}CatDogQueue;


/**
 * 猫狗队列初始化
 * @return
 */
CatDogQueue* cat_dog_queue_init();


/**
 * 队列push操作
 * @param queue
 * @param data
 */
void cat_dog_queue_push(CatDogQueue* queue, CatOrDog* data);

/**
 * 正常队列弹出
 * @param queue
 * @return
 */
void* cat_dog_queue_poll(CatDogQueue* queue);

/**
 * 只弹出一只cat
 * @param queue
 * @return
 */
void* cat_dog_queue_poll_cat(CatDogQueue* queue);

/**
 * 只弹出一只dog
 * @param queue
 * @return
 */
void* cat_dog_queue_poll_dog(CatDogQueue* queue);

/**
 * 判断队列是否空
 * @param queue
 * @return
 */
int cat_dog_queue_is_empty(CatDogQueue* queue);


/**
 * 清空队列
 * @param queue
 */
void cat_dog_queue_clear(CatDogQueue* queue);

/**
 * 释放队列内存
 * @param queue
 */
void cat_dog_queue_free(CatDogQueue* queue);

#ifdef __cplusplus
};
#endif