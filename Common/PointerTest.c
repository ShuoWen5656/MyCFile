//
// Created by 赵烁文 on 2022/9/28.
//



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){
    int *p_num = NULL, num = 3;

//    printf("the num  is %d \n", num);
//    // 查看地址使用%p 占位符
//    printf("the num address is %p \n", &num);
//
//    // 将地址给p_num
//    p_num = &num;


    // 地址是8个字节
//    printf("p_num address is %p \n", &p_num);
//    printf("p_num size is %zd\n", sizeof(p_num));
//    printf("p_num value is %p\n", p_num);
//    printf("p_num pointer value is %d\n", *p_num);
//
//
    // 验证数组引用和指针的关系
    // 数组引用是一个地址，可以和指针一样计算，但是不能更改
//    char multiple[] = "my test String";
//
//    char* p = &multiple[0];
//
//    printf("the p for [0] is %p \n", p);
//
//    p = multiple;
//
//    printf("the p for multiple is %p \n", p);
//
//    printf("the second char is %c \n ",  *(multiple + 1));


    // 可以改变地址但是不能改变内容的指针
//    const char *p_const1 = &multiple[0];

//    p_const1 = &multiple[3]; // can change addr

//    multiple = "123"; // can not change content




    // 可以改变内容但是不能改变地址的指针
//    char *const p_const2 = multiple;


//    p_const2 = &multiple[3]; // can not change addr

//    multiple = "my test String";




    // 测试二维数组的指针地址
//    char board[3][3] = {
//            {'1', '2', '3'},
//            {'4', '5', '6'},
//            {'7', '8', '9'}
//    };
//
//    for (int i = 0; i < sizeof(board); ++i){
//        printf("line %d is %c \n", i,*(*board + i));
//    }
//
//
//
//    // 申请内存 100个字节
//    int *p_int = (int*)malloc(100);
//
//    // 释放内存
//    free(p_int);
//    p_int = NULL;


    // 获取质数程序










}


