//
// Created by 赵烁文 on 2023/1/7.
//

#ifndef MYCPROJECT_ARRAYLIST_H
#define MYCPROJECT_ARRAYLIST_H

#endif //MYCPROJECT_ARRAYLIST_H

/**
 * 类似于java ArrayList功能
 * 1、元素地址连续，支持随机访问
 * 2、支持增删改查
 * 3、支持动态扩容
 */

// 列表的初始化大小
#define INIT_SIZE 15
// 扩容倍数
#define INCREASE_PERC 1.5


// 列表元素结构
typedef struct Data{
    void *data;
}Data;


// 列表结构
typedef struct ArrayList {
    // 存储数据的开头，随机访问直接游标即可
    Data *list;

    // 当前列表长度
    int len;
    // 列表所占大小
    int size;
}ArrayList;

// 定义函数原型用来操作和查询ArrayList



/**
 * 初始化列表
 * @return 成功时返回ArrayList结构地址
 */
ArrayList init_array_list();







