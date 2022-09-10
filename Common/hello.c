/**
 * written by swzhao
 * Copyright 2022
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stddef.h>
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
    // 测试格式说明符格式化长度使用
    double test_float1 = 10.1234567f;
    float test_float2 = 4.1542343f;
    float test_float3 = 0.0f;

    /**
     * 获取各种类型的数值所用得格式说明符, &为寻址运算符
     */
    // short类型
//    scanf("%hd", &b);
//    // int
//    scanf("%d", &c);
//    // long
//    scanf("%ld", &d);
//    scanf("%lld", &e);
//    scanf("%f", &f1);
//    // double
//    scanf("%lf", &x1);

    /**
     * 头文件limits.h中的类型极限值
     */
    int max = INT_MAX;
    float fmax = FLT_MAX;
    /**
     * 单精度浮点数的尾数所精确的10进制小数位数，比如float为7，double为15，在float.h中定义
     */
    float fdig = FLT_DIG;

    /**
     * 类型所占字节数，stddef.h中的方法
     */
    size_t size = sizeof(long long);
    // 输出变量所占字节数
    size_t f = sizeof test_float3;



    printf("size of float is %u \n", sizeof(float));
    // 内存地址
    printf("size of float is %p \n", &size);


    // 数组的集中声明方式
    int arr[10];
    printf("size of arr is %u \n", sizeof arr);

    int arr2[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof arr2 / sizeof(arr2[0]); ++i) {
        printf("%d \n", arr2[i]);
    }







//    char inputString = '1';
//    scanf("%f", &test_float3);

//    printf("input is %3.1f", test_float3);
    
    char salary = 1;
    // .3 为小数点后3位保留,省略掉的会四舍五入
//     printf("test_float1 is %.4f, test_float2 is %2.3f, test_float3 is %.9f", test_float1, test_float2, test_float3);
    // %10.3f 为小数点后三位，总长为10位，不够10位的，左边补空格
    // 如果想要左对齐, %-10.3f,右边补空格
//    printf("test_float1 is %10.4f, test_float2 is %-10.3f, test_float3 is %.9f", test_float1, test_float2, test_float3);
    // printf("My salary is %s \n", salary);
    // printf("hello world!! \" %s\"  \t testtt \n", ZSW_NAME); // the quotation is like java's
    // printf("first string is %d" "second string is %d", 
    //                                                 123,321);
    // printf("\b hi there");





    return 0; // 返回非0，表示异常退出，main函数返回后将控制权交给操作系统
}