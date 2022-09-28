//
// Created by 赵烁文 on 2022/9/28.
//



#include <stdio.h>



int main(void){
    int *p_num = NULL, num = 3;

    printf("the num  is %d \n", num);
    // 查看地址使用%p 占位符
    printf("the num address is %p \n", &num);

    // 将地址给p_num
    p_num = &num;


    // 地址是8个字节
    printf("p_num address is %p \n", &p_num);
    printf("p_num size is %zd\n", sizeof(p_num));
    printf("p_num value is %p\n", p_num);
    printf("p_num pointer value is %d\n", *p_num);


}


