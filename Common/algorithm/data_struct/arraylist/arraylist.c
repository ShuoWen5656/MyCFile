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
 * 1、Arraylist结构分配一波内存
 * 2、给ArrayList结构中的data指针分配一波内存用来存储data结构列表
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
        // datas[i] 当指针通过数组访问返回的引用，不是地址，该引用直接表示了data，所以这里使用"."来访问data
        // 但是list是指针，表示的是地址，通过地址直接访问datas成员时，就需要使用"->"来访问
        // datas[i].data等价与 (&datas[i]) -> value，先取到引用的地址再访问data
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
            // 如果新的数组越界了则为负数,则线性增加
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
        for (int i = list->len; i < list->size; ++i) {
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
        list->len--;
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
        return 0;
    }
    if (list->len == 0) {
        return 1;
    }else {
        return 0;
    }
}




/**
 * 测试用例
 * @return
 */
//int main(void) {
//    setbuf(stdout, NULL);
//    ArrayList* list = init_array_list();
//    int ints[] = {5,4,6,3,4,5,6};
//    int len = 7;
//    for (int i = 0; i < len; ++i) {
//        array_list_insert(list, &ints[i], -1);
//    }
////    array_list_insert(list, &i,-1);
//    if (array_list_is_empty(list) == -1) {
//        printf("the list is empty \n");
//    }
//    for (int j = 0; j < len; ++j) {
//        printf("the %d num is %d \n", j,*(int*)array_list_get(list, j));
//    }
////    array_list_clear(list);
////    i=200;
////    array_list_insert(list, &i,-1);
////    printf("the first num is %d \n", *(int*)array_list_get(list, 0));
//}







