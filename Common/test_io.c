//
// Created by 赵烁文 on 2022/10/30.
//

#include <stdio.h>



int main(void) {

    float f1 = 0.0f;
    int i = 0;
    int j = 0;
    scanf("f1 = %f i = %d %d", &f1, &i, &j);

    printf_s("f1 = %-+6.2f \n i = %08d \n", f1, i);

    printf_s("j = %d \n", j);

    char c = (char)getchar();

    printf_s("%c", c);




}






