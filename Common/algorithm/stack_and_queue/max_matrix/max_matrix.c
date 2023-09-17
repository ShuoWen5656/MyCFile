//
// Created by admin on 2023/9/17.
//
/**
 * 题目：求最大子矩阵的大小
 */
#include<stdlib.h>
#include "stack.h"
#include <stdio.h>
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif

int maxMatrix(int** matrix, int row, int col);

int process(int *preArr, int col);

/**
 * 测试用例
 * @return
 */
int main() {
    int matrix1[3][4] = {
            {1,0,1,1},
            {1,1,1,1},
            {1,1,1,0}
    };
    int** matrix = calloc(3, sizeof(int[4]));
    for (int i = 0; i < 3; i++) {
        matrix[i] = calloc(4, sizeof(int));
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = matrix1[i][j];
        }
    }
//    matrix = calloc(row, sizeof(int[4]));
    int max = maxMatrix((int **) matrix, 3, 4);
    printf("%d", max);
}

/**
 * 获取矩阵中1矩阵的最大面积
 * @param matrix
 * @return
 */
int maxMatrix(int** matrix, int row, int col) {
    if (matrix == NULL || row == 0 || col == 0) {
        return 0;
    }
    // 上一行的结果
    int* preArr = calloc(col, sizeof(int));
    for (int j = 0; j < col; j ++) {
        preArr[j] = 0;
    }
    int res = 0;
    for (int i = 0; i < row; i++) {
        // 将当前行更新
        for (int j = 0; j < col; j ++) {
            preArr[j] = matrix[i][j] == 0 ? 0 : preArr[j] + 1;
        }
        // 计算当前行中的最大矩阵面积
        int curMax = process(preArr, col);
        res = res <  curMax ? curMax : res;
    }
    return res;
}

int process(int *preArr, int col) {
    int res = 0;
    int* indexArr = calloc(col, sizeof(int));
    for (int j = 0; j < col; j++) {
        indexArr[j] = j;
    }
    // 辅助栈
    Stack* stack = stack_init();
    for (int i = 0; i < col; i++) {
        if(stack_is_empty(stack) || preArr[*(int*)stack_peek(stack)] < preArr[i]) {
            // 放索引
            stack_push(stack, &indexArr[i]);
        }else if (preArr[*(int*)stack_peek(stack)] > preArr[i]){
            // 小于：计算当前栈顶的最大面积，并更新res
            while (!stack_is_empty(stack) && preArr[*(int*)stack_peek(stack)] > preArr[i]) {
                // 当前顶高度，已弹出
                int cur = preArr[*(int*)stack_poll(stack)];
                // 计算矩阵面积
                int left = stack_is_empty(stack) ? 0 : *(int*)stack_peek(stack);
                int right = i;
                int curS = (cur * (right - left));
                res = res < curS ? curS : res;
            }
            // 将当前值加入进入
            stack_push(stack, &indexArr[i]);
        }else {
            // 相等时，只记录最左边出现的位置即可，因为最大化面积,因为344455555这种最后会计算右边的全部面积，不用担心
        }
    }
    // stack可能不是空,最后一个个计算再
    while (!stack_is_empty(stack)) {
        int left = *(int*)stack_poll(stack);
        int cur = preArr[left];
        int right = col;
        int curS = cur * (right - left);
        res = res < curS ? curS : res;
    }
    return res;
}

#ifdef __cplusplus
};
#endif



