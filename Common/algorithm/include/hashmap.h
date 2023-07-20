//
// Created by 赵烁文 on 2023/7/10.
//

#ifndef MYCPROJECT_HASHMAP_H
#define MYCPROJECT_HASHMAP_H

#endif //MYCPROJECT_HASHMAP_H

#include "arraylist.h"
#include "stdbool.h"
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * 数据结构 hashmap
 * 1、支持动态扩容
 * 2、支持put、get、clear、contains。。。
 */

// 扩容因子，如果列表内容已经超过容量的0.75，则开始扩容
#define DEFAULT_LOAD_FACTOR 0.75f
// 数组最大值2^30
#define MAXIMUM_CAPACITY 1<<30
// 数组的初始化容量
#define DEFAULT_INITIAL_CAPACITY 16
// 默认单链表超过该值时使用红黑树
#define MIN_TREEIFY_CAPACITY 64
/**
 * hash 数组中的node节点
 */
typedef struct Node Node;
/**
 * hashmap数据结构
 */
typedef struct HashMap HashMap;
/**
 * 键值对结构（仅存储键值对）
 */
typedef struct Entry Entry;


struct Node {
    unsigned int hashCode;
    void* key;
    void* value;
    Node* next;
};



struct HashMap {
    // hashtable主体
    Node* nodelist;
    // 维护键值对
    ArrayList* entrySet;
    /**
     * 代表node列表长度
     */
    int nodeListSize;

    /**
     * 扩容阈值：超过改值时就会扩容并且更新该值X2
     */
    int threshold;
};

struct Entry {
    void* key;
    void* data;
};


/**
 * 初始化hashmap
 * @return
 */
HashMap* hashmap_init();

/**
 * put键值对
 * @param hashMap
 * @param key
 * @param value
 */
int hashmap_put(HashMap* hashMap, void* key, void* value);

/**
 * 获取某个key的键
 * @param hashMap
 * @param key
 * @return
 */
void* hashmap_get(HashMap* hashMap, void* key);

/**
 * 判断是否在hashmap中
 * @param hashMap
 * @param key
 * @return
 */
int hashmap_contains(HashMap* hashMap, void* key);

/**
 * 计算当前key的hashcode
 * @param key
 * @return
 */
unsigned int hashmap_hashcode(void* key);


/**
 * 获取keyset
 * @param hashMap
 * @return
 */
ArrayList* hashmap_key_set(HashMap* hashMap);

/**
 * 获取values
 * @param hashMap
 * @return
 */
ArrayList* hashmap_values(HashMap* hashMap);

/**
 * 获取values
 * @param hashMap
 * @return
 */
ArrayList* hashmap_entry_set(HashMap* hashMap);


/**
 * entry之间是否相等
 */

int entry_equals(Entry* entry1, Entry* entry2);








#ifdef __cplusplus
};
#endif


//#include <stdio.h>
//#include <.h>
//#include <string.h>
//
//#define SIZE 10
//
//// 哈希节点结构
//typedef struct Node {
//    char* key;
//    int value;
//    struct Node* next;
//} Node;
//
//// 哈希表结构
//typedef struct HashMap {
//    Node* table[SIZE];
//} HashMap;
//
//// 创建哈希节点
//Node* createNode(char* key, int value) {
//    Node* newNode = (Node*)malloc(sizeof(Node));
//    newNode->key = strdup(key);
//    newNode->value = value;
//    newNode->next = NULL;
//    return newNode;
//}
//
//// 初始化哈希表
//void initHashMap(HashMap* hashMap) {
//    for (int i = 0; i < SIZE; i++) {
//        hashMap->table[i] = NULL;
//    }
//}
//
//// 哈希函数
//int hashFunction(char* key) {
//    int hash = 0;
//    int len = strlen(key);
//    for (int i = 0; i < len; i++) {
//        hash += key[i];
//    }
//    return hash % SIZE;
//}
//
//// 向哈希表中插入键对
//void insert(HashMap* hashMap, char* key, int value) {
//    int index = hashFunction(key);
//    Node* newNode = createNode(key, value);
//
//    // 如果该位置为空，则直接插入
//    if (hashMap->table[index] == NULL) {
//        hashMap->table[index] = newNode;
//    }
//        // 如果该位置不为空，则插入到链表头部
//    else {
//        newNode->next = hashMap->table[index];
//        hashMap->table[index] = newNode;
//    }
//}
//
//// 根据键查找哈希表中的值
//int get(HashMap* hashMap, char* key) {
//    int index = hashFunction(key);
//    Node* curr = hashMap->table[index];
//
//    while (curr != NULL) {
//        if (strcmp(curr->key, key) == 0) {
//            return curr->value;
//        }
//        curr = curr->next;
//    }
//
//    // 如果找不到键，则返回一个特殊值，如-1
//    return -1;
//}
//
////函数
//int main() {
//    HashMap hashMap;
//    initHashMap(&hashMap);
//
//    // 向哈希表中插入键值对
//    insert(&hashMap, "key1", 10);
//    insert(&hashMap, "key2", 20);
//    insert(&hashMap, "key3", 30);
//
//    // 根据键查找哈希表中的
//    int value = get(&hashMap, "key2");
//    printf("Value: %d
//           ", value);
//
//    return 0;
//}