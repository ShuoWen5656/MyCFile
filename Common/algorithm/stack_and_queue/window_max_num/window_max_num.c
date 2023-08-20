//
// Created by 赵烁文 on 2023/8/20.
//
/**
 * 题目：生成窗口最大值数据
 */

#include "double_queue.h"
#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 主函数
 * @param nums
 * @return
 */
int* window_max_num(int* nums, int len, int windowSize);
/**
 * 处理队列中的值
 * @param pQueue
 * @param pInt
 * @param i
 */
void dealQueue(DoubleQueue *pQueue, int *pInt, int* indexs,int i);

int main() {
    setbuf(stdout, NULL);
    int len = 8;
    int* nums = calloc(8, sizeof(int));
    nums[0] = 4;
    nums[1] = 3;
    nums[2] = 5;
    nums[3] = 6;
    nums[4] = 2;
    nums[5] = 9;
    nums[6] = 5;
    nums[7] = 7;
//    int nums[8] = {4,3,5,6,2,9,5,7};
//    int nums[len];
//    nums = {4,3,6,5,2,9,5,7};
    int windowSize = 3;
    int* res = window_max_num(nums, len, windowSize);
    for (int i = 0; i < len - 3 + 1; i++) {
        printf("the %d th num is %d \n", i, res[i]);
    }
}


int* window_max_num(int* nums, int len, int windowSize) {
    int* indexs = calloc(8, sizeof(int));
    for (int j = 0; j < 8; j++) {
        indexs[j] = j;
    }
    DoubleQueue* doubleQueue = double_queue_init();
    // 结果数组长度
    int resLen = len - windowSize + 1;
    int* res = calloc(resLen, sizeof(int));
    for (int i = 0; i < len; i++) {
        if (i < 2) {
            // 还没到3个元素，窗口没有未完整进来
            double_queue_push(doubleQueue, &indexs[i]);
            continue;
        }
        // 处理队列
        dealQueue(doubleQueue, nums, indexs, i);
        // 将最大值放入res中
        res[i - 2] = nums[*(int*)double_queue_peek(doubleQueue)];
    }
    return res;
}



void dealQueue(DoubleQueue *doubleQueue, int *nums, int* indexs, int i) {
    // 不是空，或者大于队尾的情况，弹出队尾
    while (!double_queue_is_empty(doubleQueue)
    && nums[i] > nums[*(int*)double_queue_peek_last(doubleQueue)]) {
        double_queue_poll_last(doubleQueue);
    }
    double_queue_push(doubleQueue, &indexs[i]);
    // 处理过期
    if (*(int*)double_queue_peek_first(doubleQueue) < i - 2) {
        // 过期的
        double_queue_poll_first(doubleQueue);
    }
}


#ifdef __cplusplus
};
#endif
