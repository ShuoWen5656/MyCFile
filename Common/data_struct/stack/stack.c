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
    return array_list_insert(arrayList, p_data, -1);
}

/**
 * 弹出一个元素
 * @param stack
 * @return
 */
int stack_poll(Stack* stack) {
    return 0;
}

/**
 * 判断栈是否为空
 * @param stack
 * @return
 */
int stack_is_empty(Stack* stack) {
    return 0;
}

/**
 * 获取栈顶元素
 * @param stack
 * @return
 */
int stack_peek(Stack* stack) {
    return 0;
}

/**
 * 清空栈
 * @param stack
 */
void stack_clear(Stack* stack) {
    return;
}

/**
 * 释放栈内存
 * @param stack
 */
void stack_free(Stack* stack) {
    return;
}



