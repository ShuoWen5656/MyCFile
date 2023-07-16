//
// Created by 赵烁文 on 2023/7/11.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#include "hashmap.h"

/***************************************************
 *          该文件为头文件hashmap.h的方法实现            *
 ***************************************************/

/********函数签名*****************/
Node *create_node(void *pVoid, void *pVoid1, unsigned int hashcode);


/**
 * 初始化hashmap
 * @return
 */
HashMap* hashmap_init(){
    HashMap* hashMap = NULL;
    hashMap = calloc(1, sizeof(HashMap));
    hashMap->entrySet = init_array_list();
    hashMap->nodelist = calloc(DEFAULT_INITIAL_CAPACITY, sizeof(Node));
    // 初始化nodeList
    hashMap->nodeListSize = DEFAULT_INITIAL_CAPACITY;
    // 初始化所有的头结点
    for (int i = 0; i < hashMap->nodeListSize; i++) {
        hashMap->nodelist[i].key = 0;
    }
    return hashMap;
}



/**
 * put键值对
 * @param hashMap
 * @param key
 * @param value
 */
int hashmap_put(HashMap* hashMap, void* key, void* value) {
    if (hashMap == NULL) {
        return 0;
    }
    // 获取存储实例
    Node* nodes = hashMap->nodelist;
    ArrayList* entrySet = hashMap->entrySet;
    // 计算需要放置的地方
    unsigned int hashcode = hashmap_hashcode(key, hashMap->nodeListSize);
    unsigned int index = hashcode % hashMap->nodeListSize;
    // 创建当前节点
    Node* curNode = create_node(key, value, hashcode);
    // 获取当前链表的头节点
    Node node = nodes[index];
    // todo 考虑一下扩容时问题
    if (node.key == 0) {
        // 说明当前列表为空,则当前节点就是头结点
        nodes[index].key = curNode->key;
        nodes[index].value = curNode->value;
        nodes[index].hashCode = curNode->hashCode;
        nodes[index].next = curNode->next;
        // 加入entryset
        array_list_insert(entrySet, curNode, -1);
        return 1;
    }else{
        // hash冲突，则加入链表结尾即可
        // 找到单链表结尾
        while (node.next != NULL) {
            node = *node.next;
        }
        node.next = curNode;
        array_list_insert(entrySet, curNode, -1);
        return 1;
    }
}

Node *create_node(void *key, void *value, unsigned int hashcode) {
    Node* res = calloc(1, sizeof(Node));
    res->key = key;
    res->value = value;
    res->hashCode = hashcode;
    res->next = NULL;
    return res;
}

/**
 * 获取某个key的键
 * @param hashMap
 * @param key
 * @return
 */
void* hashmap_get(HashMap* hashMap, void* key) {

}

/**
 * 判断是否在hashmap中
 * @param hashMap
 * @param key
 * @return
 */
int hashmap_contains(HashMap* hashMap, void* key) {

}

/**
 * 计算当前key的hashcode
 * @param key
 * @return
 */
unsigned int hashmap_hashcode(void* key, int size) {
    // 将地址转成无符号整形，保留指针的位模式
    uintptr_t keyPtr = (uintptr_t)key;
    // 高低16位异或
    unsigned int hashcode = keyPtr ^ (keyPtr >> 16);
    return hashcode;
}


/**
 * 获取keyset
 * @param hashMap
 * @return
 */
ArrayList* hashmap_key_set(HashMap* hashMap) {

}

/**
 * 获取values
 * @param hashMap
 * @return
 */
ArrayList* hashmap_values(HashMap* hashMap) {

}

/**
 * entry之间是否相等
 */

int entry_equals(Entry* entry1, Entry* entry2);


/**
 * 测试用例
 * @return
 */
int main() {
    return 0;
}
