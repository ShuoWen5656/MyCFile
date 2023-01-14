//
// Created by 赵烁文 on 2023/1/7.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#include "arraylist.h"

/********************************************
 *          该文件为头文件的方法实现            *
 ********************************************/

/**
 * 初始化列表:申请一块内存并初始化完成后，将内存的地址返回
 * 1、给list数组分配内存
 * 2、初始化各变量长度
 * @return 成功时返回ArrayList结构地址
 */
ArrayList* init_array_list(){
    int i = 0;
    // 先给列表分配内存
    ArrayList* list = calloc(1, sizeof(ArrayList));
    if (NULL == list) {
        return NULL;
    }
    // 在给列表中的data分配内存
    list->datas = calloc(INIT_SIZE, sizeof(Data));
    if (NULL == list->datas) {
        return NULL;
    }
    for (i = 0; i < INIT_SIZE; ++i)
    {
        // 地址给0相当于null
        list->datas[i].data = 0;
    }
    // 元素长度
    list->len = 0;
    // data内存长度
    list->size = INIT_SIZE;
    return list;
}

/**
 * 插入一个元素
 * @param list
 * @param p_data
 * @param index 如果为0，则从头插入，如果为-1, 则从尾部插入
 * @return
 */
int array_list_insert(ArrayList *list, void* p_data, long index){
    // 如果要扩容，则扩容后的内存量
    int relloc_size = 0;
    // 参数校验.list不为null，index不可以越界
    if (NULL == list || index < -1 || index >= list->len) {
        return -1;
    }
    // 判断扩容,未插入前如果长度还剩一个位置，则开始扩容
    if (list->len == list -> size - 1) {
        // 判断1.5倍是否越界
        int newCapacity = list->size * INCREASE_PERC;
        if (newCapacity - INT_MAX > 0) {
            // 新的数组越界了,则线性增加
            newCapacity = list->size+1;
        }
        if (newCapacity - INT_MAX > 0) {
            // 还是大于最大值，则返回-1
            return -1;
        }
        // 重新分配内存
        list->datas = realloc(list->datas, sizeof(Data) * newCapacity);
        if (NULL == list->datas) {
            // 分配内存失败
            return -1;
        }
        // 新分配的内存需要初始化
        for (int i = list->len; i < list->len; ++i) {
            list->datas[i].data = 0;
        }
        list->size = newCapacity;
    }
    // 放入新的data
    if (-1 == index) {
        // 插入尾部
        list->datas[list->len].data = p_data;
    }else {
        // 插入指定位置
        void* tem = p_data;
        void* tem2 = NULL;
        for (int i = index; i <= list->len; ++i) {
            tem2 = list->datas[i].data;
            list->datas[i].data = tem;
            tem = tem2;
        }
    }
    list->len++;
    return 1;
}



/**
 * 获取一个元素
 * @param list
 * @param index
 * @return 直接返回数据指针
 */
void* array_list_get(ArrayList* list, long index) {
    // 参数校验
    if (NULL == list || index < -1 || index >= list->len) {
        return NULL;
    }
    // index = -1 返回最后一个元素
    return index == -1 ? list->datas[list->len-1].data : list->datas[index].data;
}

/**
 * 删除元素
 * @param list
 * @param index
 */
void array_list_remove_at(ArrayList* list, long index) {
    // 参数校验
    if (NULL == list || index < -1 || index >= list->len) {
        return;
    }
    if (index == -1) {
        // 删除最后一个元素
        list->datas[list->len-1].data = NULL;
        return;
    }
    // 删除元素，将元素覆盖过来即可
    int next = index+1;
    for (; next < list->len; ++next) {
        list->datas[next-1].data = list->datas[next].data;
    }
    // 将最后一个元素变成null
    list->datas[next].data = NULL;
    list->len--;
    return;
}

/**
 * 清空数组元素，不释放内存
 * @param list
 */
void array_list_clear(ArrayList* list) {
    if (NULL == list) {
        return;
    }
    // 将每一个data都指向NULL
    int i = 0;
    for (i = 0; i < list->len; ++i) {
        list->datas[i].data = NULL;
    }
    // 长度改变
    list->len = 0;
    return;
}

/**
 * 释放数组内存
 * @param list
 */
void array_list_free(ArrayList* list) {
    if (NULL == list) {
        return;
    }
    // 先释放list中的datas
    if (list->datas != NULL) {
        free(list->datas);
    }
    free(list);
    return;
}

/**
 * 判空
 * @param list
 * @return
 */
int array_list_is_empty(ArrayList* list) {
    if (NULL == list) {
        return -1;
    }
    if (list->len == 0) {
        return 1;
    }else {
        return -1;
    }
}




/**
 * 测试用例
 * @return
 */
int main(void) {

    ArrayList* list = init_array_list();
    int i = 100;
    array_list_insert(list, &i,-1);
    if (array_list_is_empty(list) == -1) {
        printf("the list is empty \n");
    }
    array_list_clear(list);
    i=200;
    array_list_insert(list, &i,-1);
    printf("the first num is %d \n", *(int*)array_list_get(list, 0));
}







