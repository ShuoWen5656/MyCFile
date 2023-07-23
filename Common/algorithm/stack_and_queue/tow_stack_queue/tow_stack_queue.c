//
// Created by 赵烁文 on 2023/7/22.
//
/**
 * 题目：由两个栈组成的队列
 */

#include <stdlib.h>
#include <stdio.h>
#include "tow_stack_queue.h"
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * instack 内容到 outstack
 * @param source
 * @param target
 */
void in2out(Stack *source, Stack *target);

void* poll_or_peek(TowStackQueue *towStackQueue, int isPeek);



/**
 * 构造函数
 * @return
 */
TowStackQueue* tow_stack_queue_init() {
    TowStackQueue* towStackQueue = calloc(1, sizeof(TowStackQueue));
    towStackQueue->stackIn = stack_init();
    towStackQueue->stackOut = stack_init();
    towStackQueue->size = 0;
    return towStackQueue;
}

/**
 * 加入队头
 * @param towStackQueue
 * @param data
 */
void tow_stack_queue_add(TowStackQueue* towStackQueue, void* data) {
    if (towStackQueue == NULL) {
        return;
    }
    // 直接元素接入stackin即可
    Stack* stackIn = towStackQueue->stackIn;
    int size = towStackQueue->size;
    stack_push(stackIn, data);
    towStackQueue->size = ++size;
}

/**
 * 从队尾弹出
 * @param towStackQueue
 * @return
 */
void* tow_stack_queue_poll(TowStackQueue* towStackQueue) {
    return poll_or_peek(towStackQueue, 0);
}

/**
 * 查看当前队尾
 * @param towStackQueue
 * @return
 */
void* tow_stack_queue_peek(TowStackQueue* towStackQueue) {
    return poll_or_peek(towStackQueue, 1);
}

/**
 * 清空所有元素
 * @param towStackQueue
 */
void tow_stack_queue_clear(TowStackQueue* towStackQueue) {
    if (towStackQueue == NULL) {
        return;
    }
    Stack* outStack = towStackQueue->stackOut;
    Stack* inStack = towStackQueue->stackIn;
    stack_clear(outStack);
    stack_clear(inStack);
    towStackQueue->size = 0;
}

/**
 * 释放所有元素的内存
 * @param towStackQueue
 */
void tow_stack_queue_free(TowStackQueue* towStackQueue) {
    if (towStackQueue == NULL) {
        return;
    }
    Stack* outStack = towStackQueue->stackOut;
    Stack* inStack = towStackQueue->stackIn;
    if (outStack != NULL) {
        stack_free(outStack);
    }
    if (inStack != NULL) {
        stack_free(inStack);
    }
    free(towStackQueue);
}

/******************非暴露接口实现*********************/

void in2out(Stack *source, Stack *target) {
    while (!stack_is_empty(source)) {
        stack_push(target, stack_poll(source));
    }
}

/**
 * poll出元素或者peek元素
 * @param pQueue
 * @param i
 */
void* poll_or_peek(TowStackQueue *towStackQueue, int isPeek) {
    if (towStackQueue == NULL) {
        return NULL;
    }
    Stack* outStack = towStackQueue->stackOut;
    Stack* inStack = towStackQueue->stackIn;
    if (stack_is_empty(outStack) && stack_is_empty(inStack)) {
        return NULL;
    }
    if (!stack_is_empty(outStack)) {
        // 如果不空直接弹出返回即可
        return stack_poll(outStack);
    }else {
        // 空的话需要先将in转到out中
        in2out(inStack, outStack);
        if (isPeek == 1) {
            stack_peek(outStack);
        }else if(isPeek == 0) {
            stack_poll(outStack);
            int size = towStackQueue->size;
            towStackQueue->size = --size;
        }
    }
}


//int main() {
//    setbuf(stdout, NULL);
//    TowStackQueue* towStackQueue = tow_stack_queue_init();
//    int elms[] = {6,5,4,3,2,1};
//    int size = 6;
//    for (int i = 0; i < 3; i++) {
//        tow_stack_queue_add(towStackQueue, &elms[i]);
//    }
//    int res1 = *(int*)tow_stack_queue_peek(towStackQueue);
//    int res2 = *(int*)tow_stack_queue_poll(towStackQueue);
//    for (int i = 3; i < size; i++) {
//        tow_stack_queue_add(towStackQueue, &elms[i]);
//    }
//    int res3 = *(int*)tow_stack_queue_poll(towStackQueue);
//}


#ifdef __cplusplus
};
#endif
