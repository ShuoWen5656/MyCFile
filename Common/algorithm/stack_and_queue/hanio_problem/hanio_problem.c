//
// Created by 赵烁文 on 2023/7/27.
//

/**
 * 问题：用栈来求解汉诺塔问题
 * 要求：form到to不能直接越过中间
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <math.h>
#include <time.h>
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif
/**
* 定义枚举的5个动作
*/
enum Action{NO, L2M, M2L, R2M, M2R};
/**
 * 能够存储上一个操作的结构
 */
typedef struct Record{
    enum Action action;
}Record;

/**
 * 递归法
 * 从 from到to num个圆盘
 * @param i
 * @param left
 * @param mid
 * @param right
 * @param left1
 * @param right1
 */
void hanio_problem_process(int num, char *left, char *mid, char *right, char *from, char *to);






/**
 * 方法二：将num个圆盘从左边往右边移动
 * @param num
 */
void hanio_problem_process2(int num);

/**
 * process2的子流程
 * @param record
 * @param actionRev
 * @param action
 * @param stack_l
 * @param stack_m
 * @param main
 */
void hanio_problem_process21(Record *record, enum Action actionRev, enum Action action, Stack *stack_l, Stack *stack_m,
                             Stack *stack_r);


/**
 * 测试用例
 * @return
 */
int main() {
    // 申请三个地址作为三个柱子
    char* left = "left";
    char* right = "right";
    char* mid = "mid";
    int num = 2;
    hanio_problem_process2(num);
//    hanio_problem_process(2,left, mid, right, left, right);


}

void hanio_problem_process2(int num) {
    // 初始化结构
    Record* record = calloc(1, sizeof(Record));
    record->action = NO;
    // 申请三个栈，并放入对应数值
    Stack* stack_l = stack_init();
    Stack* stack_r = stack_init();
    Stack* stack_m = stack_init();
    int max = INT_MAX;
    stack_push(stack_l, &max);
    stack_push(stack_r, &max);
    stack_push(stack_m, &max);
    // 塔数量
    // 没有容器的话，局部变量地址会失效
    int* container = calloc(2, sizeof(int));
    for (int i = num; i > 0; i--) {
        container[i-1] = i;
        stack_push(stack_l, &container[i-1]);
    }
    // 开始模拟移动,当右边的圆盘个数为num时说明移动完毕
    while (stack_r->arrayList->len != num+1) {
        // 一共就四种可能，都用一遍
        hanio_problem_process21(record, M2L, L2M, stack_l, stack_m, stack_r);
        hanio_problem_process21(record, L2M, M2L, stack_l, stack_m, stack_r);
        hanio_problem_process21(record, R2M, M2R, stack_l, stack_m, stack_r);
        hanio_problem_process21(record, M2R, R2M, stack_l, stack_m, stack_r);
    }

}

void hanio_problem_process21(Record *record, enum Action actionRev, enum Action action, Stack *stack_l, Stack *stack_m,
                             Stack *stack_r) {
    Stack* from = NULL;
    Stack* to = NULL;
    char * msg = NULL;
    // 首先判断from和to
    if (action == L2M) {
        from = stack_l;
        to = stack_m;
        msg = "form left to mid\n";
    }else if(action == M2L) {
        from = stack_m;
        to = stack_l;
        msg = "form mid to left\n";
    }else if (action == M2R) {
        from = stack_m;
        to = stack_r;
        msg = "form mid to right\n";
    }else if (action == R2M) {
        from = stack_r;
        to = stack_m;
        msg = "form right to mid\n";
    }
    // 1、首先最优解不可能有逆过程2、其次当前操作action不能导致栈顶大于栈底
    if (record->action != actionRev && (*(int*)stack_peek(from)) < (*(int*)stack_peek(to))) {
        stack_push(to, stack_poll(from));
        printf("%s", msg);
        // 上一个action更换
        record->action = action;
    }
}

void hanio_problem_process(int num, char *left, char *mid, char *right, char *from, char *to) {
    // 先计算出other
    char * other = NULL;
    if (from != left && to != left) {
        other = left;
    }else if (from != right && to != right) {
        other = right;
    }else {
        other = mid;
    }
    if (num == 0){
        return;
    }else if(num == 1) {
        if (other == mid) {
            // 说明中间要过一下
            printf("from %s to mid\n", from);
        }
        printf("from mid to %s\n", to);
    }else {
        // 将上面n-1作为一个整体
        if (other == mid) {
            // 说明中间隔了一个
            hanio_problem_process(num-1, left, mid, right, from, to);
            // 到中间
            printf("from %s to mid\n", from);
            hanio_problem_process(num-1, left, mid, right, to, from);
            printf("from mid to %s\n", to);
            hanio_problem_process(num-1, left, mid, right, from, to);
        }else {
            // 中间没有隔
            hanio_problem_process(num-1, left, mid, right, from, other);
            // 到中间
            printf("from %s to %s\n", from, to);
            hanio_problem_process(num-1, left, mid, right, other, to);
        }
    }
}


#ifdef __cplusplus
};
#endif
