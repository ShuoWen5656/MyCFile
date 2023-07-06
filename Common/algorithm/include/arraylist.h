//
// Created by 赵烁文 on 2023/1/7.
//

#ifndef MYCPROJECT_ARRAYLIST_H
#define MYCPROJECT_ARRAYLIST_H

#endif //MYCPROJECT_ARRAYLIST_H

/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 类似于java ArrayList功能
 * 1、元素地址连续，支持随机访问
 * 2、支持增删改查
 * 3、支持动态扩容
 */



/**
 * 列表初始化配置
 */
// 列表的初始化大小
#define INIT_SIZE 5
// 扩容倍数
#define INCREASE_PERC 1.5


/**
 * 列表的结构名称定义
 */
// 定义
typedef struct Data Data;
typedef struct ArrayList ArrayList;

/**
 * 列表的结构定义(相当于对象,但是方法定义不在对象中)
 */
// 列表元素，内部统一封装了一个指向内存的指针，可以不确定类型
struct Data {
    void *data;
};
// 列表，维护一个指向任何地方的指针，并且维护整个列表的长度和所占内存的大小，此处的内存指的是指针占的内存
struct ArrayList {
    // 存储数据的开头，随机访问直接游标即可
    Data* datas;
    // 当前列表有效元素长度
    int len;
    // 列表所占内存大小
    int size;
};


/*****************************************************************************
 * 定义操作结构的方法，相当于对象中的方法，c语言面向过程编程，也就是面向函数编程，主体是函数*
 * ***************************************************************************/
/**
 * 初始化列表
 * 1、给list数组分配内存
 * 2、初始化各变量长度
 * @return 成功时返回ArrayList结构地址
 */
ArrayList* init_array_list();


/**
 * 插入一个元素
 * @param list
 * @param p_data
 * @param index 如果为0，则从头插入，如果为-1,则从尾部插入
 * @return
 */
int array_list_insert(ArrayList *list, void* p_data, long index);

/**
 * 获取一个元素
 * @param list
 * @param index
 * @return 直接返回数据指针
 */
void* array_list_get(ArrayList* list, long index);

/**
 * 删除元素
 * @param list
 * @param index
 */
void array_list_remove_at(ArrayList* list, long index);

/**
 * 清空数组元素，不释放内存
 * @param list
 */
void array_list_clear(ArrayList* list);

/**
 * 释放数组内存
 * @param list
 */
void array_list_free(ArrayList* list);

/**
 * 判空
 * @param list
 * @return
 */
int array_list_is_empty(ArrayList* list);


#ifdef __cplusplus
};
#endif




