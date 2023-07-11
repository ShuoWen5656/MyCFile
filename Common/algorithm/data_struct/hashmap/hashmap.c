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
/**
 * put键值对
 * @param hashMap
 * @param key
 * @param value
 */
void hashmap_put(HashMap* hashMap, void* key, void* value) {

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
int hashmap_hashcode(void* key) {

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


