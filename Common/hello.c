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
    long int d = 1L;
    long long e = 1LL;
    // 5个无符号
    unsigned char a1 = '1'; // 无符号类型 8位
    unsigned short b1 = 1; // 16位
    unsigned int c1 = 1U;  // 32
    unsigned long d1 = 1UL; // 32
    unsigned long long e1 = 1ULL; // 64
    // 16进制表示数字
    long d2 = 0xEEEDCL;
    unsigned long long e2 = 0xFDDABBULL;
    // 8进制:由于以前存在36位机器，所以出现8进制数
    long d3 = 0543154L;
    unsigned long long e3 = 0123414125ULL;
    
    float f1 = 1.0f; // 32
    double x1 = 1.0; // 64
    long double x2 = 1.0L; // 92

    double test_float1 = 10.1234567f;
    float test_float2 = 4.0f;
    float test_float3 = 0.0f;


    
    char salary = 1;
    printf("test_float1 is %.99f, test_float2 is %.3f, test_float3 is %.9f", test_float1, test_float2, test_float3);

    // printf("My salary is %s \n", salary);
    // printf("hello world!! \" %s\"  \t testtt \n", ZSW_NAME); // the quotation is like java's
    // printf("first string is %d" "second string is %d", 
    //                                                 123,321);
    // printf("\b hi there");
    return 0; // 返回非0，表示异常退出，main函数返回后将控制权交给操作系统
}