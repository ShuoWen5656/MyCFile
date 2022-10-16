//
// Created by 赵烁文 on 2022/10/6.
//

// 测试函数和函数原型


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 多变元库
#include <stdarg.h>

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
inline double Average(double*, size_t);


/**
 * 多变元函数
 */
double Average_va(double v1, double v2, ...);


/**
 * 执行函数指针的函数
 * @param p_func
 * @param ...
 * @return
 */
double any_func(double (*p_func)(double*, size_t), double*, size_t);


// main函数由主机函数调用，无需函数原型
int main(int argc, char* argv[])
{
    setbuf(stdout, NULL);

    // 创建一个长度固定的数组,初始化都是0.0
    double params[MAX_LEN] = {0.0};
    size_t consumeNum = MAX_LEN;
    // 将自定义长度赋值给consumeNum
    scanf("%zd", &consumeNum);
    // 获取consumeNum个数字保存到params
    size_t size = GetData(params, (int)consumeNum > MAX_LEN ? MAX_LEN : consumeNum);
    printf("the size is %zu \n", size);
    printf("the size2 is %zu \n", sizeof(params));

    // 求平均值
    double average = any_func(Average, params, consumeNum);
//     多变元一定要协商好变元类型和变元结束点
//    double average = Average_va((double)0.1, (double)0.2, (double)0.3, (double)0.4, (double)0.0);

    // 申明一个函数指针
//    double (*p_average) (double, double, ...);
//    p_average = Average_va;
//    double average = p_average(0.1, 0.2, 0.3, 0.4, 0.8,2.0, 0.0);
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

inline double Average_va(double v1, double v2, ...) {
    // 多变元指针起点
    va_list p_arg = NULL;

    // 获取多变元起点赋值给指针,v2为固定变元的最后一个值
    va_start(p_arg, v2);
    int count = 2;
    double value;
    double sum = v1 + v2;
    // va_arg 从起点开始按照给定的类型（double）切割字节数转成对应类型并返回,p_arg会一直被赋值给切割后的下一个地址起始处
    while ((value = va_arg(p_arg, double)) != 0.0) {
        sum += value;
        count ++;
    }
//    abort();
    va_end(p_arg);
    return sum/count;
}



double any_func(double (*p_func)(double*, size_t), double* params, size_t size) {
    return p_func(params, size);
}










