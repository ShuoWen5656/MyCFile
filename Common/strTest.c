//
// Created by 赵烁文 on 2022/9/10.
//


#define __STDC_WANT_LIB_EXT1__1

#include <stdio.h>
#include <string.h>




int main(void){


    char str[] = "my string 666\n";

    char str2[][40] = {
            "my first str",
            "my second str"
    };


    printf_s("this is \" %s \" \n", str);

    printf("len of str2 is %zu\n", sizeof(str2));

    // 计算真实的str长度
    for (int i = 0; i < sizeof(str2)/ sizeof(str2[0]); ++i)
    {
        printf("str%d is \"%s\" \n", i, str2[i]);
        printf("str%d len is %zu \n", i, strnlen(str2[i], sizeof(str2[i])));
    }


    char str_cp[25];
    char str_temp[25];
    for (int i = 0; i < sizeof(str2)/ sizeof(str2[0]); ++i){
        strcat(str_temp, str2[i]);
        printf("str_temp len is %zu \n", strnlen(str_temp, sizeof(str_temp)));
    }

    strcpy(str_cp, str_temp);

    printf("str_cp len is %zu \n", strnlen(str_cp, sizeof(str_cp)));











}