//
// Created by 赵烁文 on 2022/10/6.
//

// 测试函数和函数原型


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 100
// 定义函数原型

/**
 * 函数原型：double类型的容器，容器的大小
 * @return
 */
size_t GetData(double[], size_t);

/**
 * 函数原型： 将double类型的数组求和
 * @return
 */
double Sum(const double*, size_t);

/**
 * 函数原型：求double数组的平均值
 * @return
 */
double Average(double*, size_t);

// main函数由主机函数调用，无需函数原型
int main(void)
{
    setbuf(stdout, NULL);

    // 创建一个长度固定的数组,初始化都是0.0
    double params[MAX_LEN] = {0.0};
    size_t consumeNum = MAX_LEN;
    // 将自定义长度赋值给consumeNum
    scanf("%zd", &consumeNum);
    // 获取consumeNum个数字保存到params
    size_t size = GetData(params, consumeNum > MAX_LEN ? MAX_LEN : consumeNum);
    printf("the size is %zu \n", size);
    printf("the size2 is %zu \n", sizeof(params));

    // 求平均值
    double average = Average(params, consumeNum);

    printf("the average is %10.1lf \n", average);


}

// 函数定义

size_t GetData(double container[], size_t len)
{
    // 接受后并放入容器
    for (int i = 0; i < len; ++i) {
        scanf("%lf", &container[i]);
    }
    return sizeof(container);
}

double Sum(const double* arr, size_t len){
    double res = 0;
    for (int i = 0; i < len; ++i) {
        res += arr[i];
    }
    return res;
}


double Average(double* arr, size_t len){
    return Sum(arr, len)/len;
}














