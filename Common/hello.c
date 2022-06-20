/**
 * written by swzhao
 * Copyright 2022
 */
#include <stdio.h>

#define ZSW_NAME  "zsw"

/*************************************
 * I will success                    *
 * swzhao                            *
 * ***********************************/
int main(void)
{
    // 5个有符号
    signed char a = '1'; // 有符号char 8位
    short b = 1;
    int c = 1;
    long int d = 1;
    long long e = 1;
    // 5个无符号
    unsigned char a1 = '1'; // 无符号类型 8位
    unsigned short b1 = 1;
    unsigned int c1 = 1;
    unsigned long d1 = 1;
    unsigned long long e1 = 1;





    char salary = 1;
    // printf("My salary is %s \n", salary);
    // printf("hello world!! \" %s\"  \t testtt \n", ZSW_NAME); // the quotation is like java's
    printf("first string is %d" "second string is %d", 
                                                    123,321);
    // printf("\b hi there");
    return 0; // 返回非0，表示异常退出，main函数返回后将控制权交给操作系统
}