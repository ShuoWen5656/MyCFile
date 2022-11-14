//
// Created by 赵烁文 on 2022/9/10.
//


//#define _STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>


int main(void){


    char str[] = "my string 666\n";

    char str2[][40] = {
            "my first str",
            "my second str"
    };

    // 测试指针
//    char a = 'a';
//
//    char* strp = &a;
//
//    printf("strp is %zu", strp);
//    printf("strp1 is %zu", &a);
    // gets_s测试

    char gets_str[21];

//    if (fgets(gets_str, 21, stdin))
//    {
//        printf("get Str is %s", gets_str);
//    }else
//    {
//        printf("Error str!");
//    }


    char dstr[] = "0.2 0.5 0.7";


    // 滑动指针,存储的应该是数组中的地址
    char* ptr = NULL;
    char* dstrp = dstr;

    while (true){
        // 给地址的地址到函数中，函数更改地址指向的内容
        double value = strtod(dstrp, &ptr);
        if (ptr == dstrp){
            break;
        }
        printf("%f \n", value);
        dstrp = ptr;
    }

    // 10个char[]数组类型的指针
    char *p_chars[10] = {NULL};


//    printf_s("this is \" %s \" \n", str);

//    printf("len of str2 is %zu\n", sizeof(str2));

    // 计算真实的str长度
//    for (int i = 0; i < sizeof(str2)/ sizeof(str2[0]); ++i)
//    {
//        printf("str%d is \"%s\" \n", i, str2[i]);
//        printf("str%d len is %zu \n", i, strnlen(str2[i], sizeof(str2[i])));
//    }
//
//
//    char str_cp[26];
//    char str_temp[26];
//    for (int i = 0; i < sizeof(str2)/ sizeof(str2[0]); ++i){
//        strcat(str_temp, str2[i]);
//        printf("str_temp len is %zu \n", strnlen(str_temp, sizeof(str_temp)));
//    }

//    strcpy(str_cp, str_temp);
    // 检查\0
//    strncpy_s(str_cp, sizeof(str_cp),str_temp, sizeof(str_temp));
//    printf("str_cp len is %zu \n", strnlen(str_cp, sizeof(str_cp)));











}