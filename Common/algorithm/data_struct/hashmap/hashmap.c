//
// Created by 赵烁文 on 2023/7/11.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#include "hashmap.h"

/********函数签名，非接口实现,不会对外暴露*****************/
/**
 * 创建一个全新节点
 * @param pVoid
 * @param pVoid1
 * @param hashcode
 * @return
 */
Node *create_node(void *pVoid, void *pVoid1, unsigned int hashcode);
/**
 * 扩容
 * @param pMap
 */
void resize(HashMap *pMap);

/**
 * 计算当前key的hashcode
 * @param key
 * @return
 */
unsigned int hashmap_hashcode(void* key);

/***************************************************
 *          该文件为头文件hashmap.h的方法实现            *
 ***************************************************/


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
    // 默认table的75%为扩容阈值
    hashMap->threshold = DEFAULT_INITIAL_CAPACITY*DEFAULT_LOAD_FACTOR;
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
    unsigned int hashcode = hashmap_hashcode(key);
    unsigned int index = hashcode % hashMap->nodeListSize;
    // 创建当前节点
    Node* curNode = create_node(key, value, hashcode);
    // 获取当前链表的头节点
    Node node = nodes[index];
    if (node.key == 0) {
        // 说明当前列表为空,则当前节点就是头结点
        nodes[index].key = curNode->key;
        nodes[index].value = curNode->value;
        nodes[index].hashCode = curNode->hashCode;
        nodes[index].next = curNode->next;
        // 加入entryset
    }else{
        // hash冲突，如果存在该key的节点，则覆盖，否则加入链表结尾
        Node* exist = NULL;
        while (node.next != NULL) {
            if (node.key == key) {
                // 已经存在
                exist = &node;
            }
            node = *node.next;
        }
        if (exist != NULL) {
            // 已经存在key,直接修改value即可
            exist->value = value;
        }else{
            node.next = curNode;
        }
    }
    // 加入entryset
    array_list_insert(entrySet, curNode, -1);
    // 考虑扩容
    if (entrySet->len > hashMap->threshold) {
        resize(hashMap);
    }
}




/**
 * 获取某个key的键
 * @param hashMap
 * @param key
 * @return
 */
void* hashmap_get(HashMap* hashMap, void* key) {
    Node* nodeList =  hashMap->nodelist;
    int nodeListSize =  hashMap->nodeListSize;
    if (key == NULL || nodeList == NULL) {
        return NULL;
    }
    // 计算index
    uintptr_t hashcode = hashmap_hashcode(key);
    unsigned int index = hashcode % nodeListSize;
    Node* cur = &nodeList[index];
    Node* target = NULL;
    do{
        if (cur->key == key) {
            target = cur;
            break;
        }
        cur = cur->next;
    }while (cur != NULL);
    return target == NULL ? NULL : target->value;
}

/**
 * 判断是否在hashmap中
 * @param hashMap
 * @param key
 * @return
 */
int hashmap_contains(HashMap* hashMap, void* key) {
    if (hashmap_get(hashMap, key) != NULL) {
        return 1;
    } else{
        return 0;
    }
}




/**
 * 获取keyset
 * @param hashMap
 * @return
 */
ArrayList* hashmap_key_set(HashMap* hashMap) {
    return hashMap->entrySet;
}

/**
 * 获取values
 * @param hashMap
 * @return
 */
ArrayList* hashmap_values(HashMap* hashMap) {
    ArrayList* entrySet = hashMap->entrySet;
    ArrayList* res = init_array_list();
    for (int i = 0; i < entrySet->len; i++) {
        // 将当前元素插入到res的尾部
        array_list_insert(res, array_list_get(entrySet, i), -1);
    }
    return res;
}


/**
 * entry之间是否相等
 */

int entry_equals(Entry* entry1, Entry* entry2) {
    return entry1->key == entry2->key && entry1->data == entry2->data ? 1 : 0;
}

/**
 * 清理hashmap中的所有元素(尽可能的保证所有的核心数据结构地址不改变)
 * 1、清空所有单链表之后，数组的第一个元素全部初始化掉
 * 2、entryset清空
 * 3、长度和threshold暂时不缩容量
 * @param hashMap
 */
void hashmap_clear(HashMap* hashMap) {
    if (hashMap == NULL) {
        return;
    }
    Node* nodeList = hashMap->nodelist;
    for (int i = 0; i < hashMap->nodeListSize; ++i) {
        Node* curNode = &nodeList[i];
        int isFirst = 1;
        while (curNode != NULL) {
            curNode->hashCode = 0;
            curNode->key = NULL;
            curNode->value = NULL;
            // 将下一个节点地址暂存
            Node* next = curNode->next;
            // 清空当前节点的next
            curNode->next = NULL;
            // free掉除了第一个节点的后续节点的内存
            if (isFirst == 0) {
                free(curNode);
            }else {
                isFirst = 0;
            }
            curNode = next;
        }
    }
    // 清空entryset
    ArrayList* entrySet = hashMap->entrySet;
    array_list_clear(entrySet);
}

/**
 * 释放hashmap中的所有内存
 * 1、首先还是清空所有内容先
 * 2、释放所有nodelist数组内存
 * 3、释放entryset
 * 4、释放自己
 * @param hashMap
 */
void hashmap_free(HashMap* hashMap) {
    if (hashMap == NULL) {
        return;
    }
    // 1、先进行一次清空
    hashmap_clear(hashMap);
    // 2、释放数组内存
    free(hashMap->nodelist);
    // 3、释放entryset
    free(hashMap->entrySet);
    // 4、释放自己
    free(hashMap);
}







/******************************************************************************************************************
 *          一下函数为非接口实现，不对外暴露                                                                                    *
 *******************************************************************************************************************/



/**
 * 计算当前key的hashcode
 * @param key
 * @return
 */
unsigned int hashmap_hashcode(void* key) {
    // 将地址转成无符号整形，保留指针的位模式
    uintptr_t keyPtr = (uintptr_t)key;
    // 高低16位异或
    unsigned int hashcode = keyPtr ^ (keyPtr >> 16);
    return hashcode;
}

Node* create_node(void *key, void *value, unsigned int hashcode) {
    Node* res = calloc(1, sizeof(Node));
    res->key = key;
    res->value = value;
    res->hashCode = hashcode;
    res->next = NULL;
    return res;
}

/**
 * 扩容hashmap
 * 1、首先将数组扩容到原来的两倍（注意越界问题）
 * 2、数组长度永远都是2的幂次方，所以newlen = oldlen*2 = 00100000
 * oldlen = 00010000
 * 3、遍历所有的元素，对于每一个单链表来讲，遍历节点的hashcode，计算hashcode*oldlen，如果是1则作为高位元素(index+oldlen)，如果是0作为低位元素（index）
 * 4、新的长度更新，新的阈值更新
 * @param pMap
 */
void resize(HashMap *hashMap) {
    // 此处需要校验一下越界
    int oldCap = hashMap->nodeListSize;
    if (oldCap == INT_MAX) {
        // 已经最大值，则不用扩容了
        return;
    }
    int newCap = oldCap * 2 > INT_MAX ? INT_MAX : oldCap * 2;
    Node* nodelist = hashMap->nodelist;
    // 申请新的内存
    Node* newNodeList = calloc(newCap, sizeof(Node));
    // 遍历所有节点
    for (int i = 0; i < oldCap; i++){
        // 低位头尾
        Node* lowHead = NULL;
        Node* lowTail = NULL;
        // 高位头尾
        Node* highHead = NULL;
        Node* highTail = NULL;
        // 取出当前列表头结点
        Node* cur = &nodelist[i];
        if (cur->hashCode == 0) {
            // 说明当前列没有值,直接下一列
            continue;
        }
        while (cur != NULL) {
            unsigned int hashCode = cur->hashCode;
            if ((hashCode & (unsigned)oldCap) == 0) {
                // 低位
                if (lowHead == NULL) {
                    // 初始化
                    lowHead = cur;
                    lowTail = cur;
                }else {
                    lowTail->next = cur;
                }
            }else {
                // 高位
                if (highHead == NULL) {
                    highHead = cur;
                    highTail = cur;
                } else{
                    highTail->next = cur;
                }
            }
            cur = cur->next;
        }
        // 结束之后，将高低位放回原来的地方
        if (lowHead != NULL) {
            newNodeList[i] = *lowHead;
            lowTail->next = NULL;
        }
        if (highHead != NULL) {
            newNodeList[i+oldCap] = *highHead;
            highTail->next = NULL;
        }
    }
    // 结束之后将新的节点列表赋值回去
    hashMap->nodelist = newNodeList;
    // 更新链表长度和下一次的阈值更新
    hashMap->nodeListSize = newCap;
    hashMap->threshold = newCap * 2;
}


///**
// * 测试用例
// * @return
// */
//int main() {
//    // 申请一个map
//    HashMap* hashMap = hashmap_init();
//    int size = 14;
//    int keys[14] = {0};
//    int values[14] = {0};
//    for (int i = 0; i < size; i++) {
//        keys[i] = i;
//        values[i] = size-i;
//        hashmap_put(hashMap, &keys[i], &values[i]);
//    }
//    int* p1 = hashmap_get(hashMap, &keys[0]);
//    int* p2 = hashmap_get(hashMap, &keys[2]);
//
//    return 0;
//}
