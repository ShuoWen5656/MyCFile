//
// Created by 赵烁文 on 2023/1/15.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#include "stack.h"

/***************************************************
 *          该文件为头文件Stack.h的方法实现            *
 ***************************************************/


/**
 * 初始化栈结构
 * 相当于new
 * 1、初始化ArrayList
 * 2、
 * @return
 */
Stack* stack_init() {
    Stack* stack = NULL;
    // 为stack指针分配1个大小为Stack的内存
    stack = calloc(1, sizeof(Stack));
    // 初始化stack中的ArrayList
    stack->arrayList = init_array_list();
    return stack;
}

/**
 * 加入一个元素
 * @param stack
 * @param p_data
 * @return
 */
int stack_push(Stack* stack, void* p_data) {
    // 拿出主角出来操作
    ArrayList* arrayList = stack->arrayList;
    // 将当前元素添加到list的尾部
    return array_list_insert(arrayList, p_data, -1);
}

/**
 * 弹出一个元素
 * @param stack
 * @return
 */
void* stack_poll(Stack* stack) {
    ArrayList* arrayList = stack->arrayList;
    // 获取尾巴元素所在的内存地址
    void* res = array_list_get(arrayList, -1);
    if (res == NULL) {
        // 地址为0
        return 0;
    }
    // 将尾巴的元素删除
    array_list_remove_at(arrayList, -1);
    return res;
}

/**
 * 判断栈是否为空
 * @param stack
 * @return
 */
int stack_is_empty(Stack* stack) {
    ArrayList* arrayList = stack->arrayList;
    return array_list_is_empty(arrayList);
}

/**
 * 获取栈顶元素
 * @param stack
 * @return
 */
void* stack_peek(Stack* stack) {
    ArrayList* arrayList = stack->arrayList;
    return array_list_get(arrayList, -1);
}

/**
 * 清空栈
 * @param stack
 */
void stack_clear(Stack* stack) {
    ArrayList* arrayList = stack->arrayList;
    // 先清空arraylist中的元素
    array_list_clear(arrayList);
    // stack不用清空
    return;
}

/**
 * 释放栈内存
 * @param stack
 */
void stack_free(Stack* stack) {
    if (stack == NULL){
        return;
    }
    ArrayList* arrayList = stack->arrayList;
    // 释放arr中的内存
    if (arrayList != NULL) {
        array_list_free(arrayList);
    }
    free(stack);
    return;
}


///**
// * 测试用例
// * @return
// */
//int main() {
//
//    Stack* stack = stack_init();
//    int ints[3] = {1,2,3};
//    int len = 3;
//    for (int i = 0; i < len; i++) {
//        stack_push(stack, &ints[i]);
//    }
//    for (int i = 0; i < len; i++) {
//        printf("first is  %d", *(int*)stack_poll(stack));
//    }
//}


