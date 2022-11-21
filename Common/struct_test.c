//
// Created by 赵烁文 on 2022/11/3.
//

#include <stdio.h>

struct List {
    int len;
    int arr[16];
};

typedef struct List List;


int main(void) {
    List list = {.len = 3, .arr = {1,2,3}};




    printf("len is %d \n", list.len);


    for (int i = 0; i < list.len; ++i) {
        printf("arr[%d] is %d \n", i, list.arr[i]);
    }


}



