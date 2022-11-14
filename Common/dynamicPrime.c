//
// Created by 赵烁文 on 2022/10/5.
//

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main(void){
    // printf使用buf缓存输出，等待结束后才能看到控制台，这里禁用一下buf可以调试出控制塔
    setbuf(stdout, NULL);
    // 最少获取数量
    int total = 4;
    // 动态内存分配指针，保存total个int类型的整数
    int* p_prime = NULL;
    // 计数器
    int count = 4;
    // 当前整数,用来做被除数的
    int cur = 0;
    // 获取手动输入的total
    scanf("%d", &total);

    // 至少四个
    total = total > 4? total : 4;


    printf("will get %d prime num:", total);




    // 分配内存
    p_prime = malloc(total*sizeof(int));


//    p_prime = calloc(total, sizeof(int));

    // 扩容
//    realloc(p_prime, total + 2);
    // 如果分配失败会返回null
    if (!p_prime){
        printf("fail to malloc");
    }
    // 前四个数先初始化 1、2、3、5
    *(p_prime) = 1;
    *(p_prime + 1) = 2;
    *(p_prime + 2) = 3;
    *(p_prime + 3) = 5;

    cur = 5;

    w0:
    while (count < total){
        // 循环查找一个
        cur += 2;
        for (int i = 1; i < count; ++i) {
            if (cur % *(p_prime + i) == 0){
                // 整除了就下一个
                goto w0;
            }
        }
        // 循环结束了说明是质数
        *(p_prime + count) = cur;
        count ++;
    }

    printf("\n");
    // 最后输出
    for (int j = 0; j < count; ++j) {
        printf("%12d", *(p_prime + j));
        if ((j+1)%5 == 0){
            printf("\n");
        }
    }

    // 释放内存
    free(p_prime);
    p_prime = NULL;













}