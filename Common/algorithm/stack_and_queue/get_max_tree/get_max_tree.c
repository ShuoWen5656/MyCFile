//
// Created by admin on 2023/9/9.
//
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "get_max_tree.h"
#include <math.h>
#include <limits.h>
/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/


TreeNode *convert2Nodes(const int *arr, int size);


void deal(Stack *pStack, TreeNode *pNode[], TreeNode* node, int i);

#ifdef __cplusplus
extern "C"
{
#endif



/**
 * 测试用例
 * @return
 */
//int main() {
//    int arr[5] = {3,4,5,1,2};
//    TreeNode* res = getMaxNode(arr , 5);
//    printf("parent is %d", res->value);
//}

/**
 * 获取最大树
 * @return
 */
TreeNode* getMaxNode(int arr[], int size) {
    TreeNode* node_arrays = convert2Nodes(arr, size);
    // leftMax[i]表示arr[i]左边第一个比自己大的node
    TreeNode* leftMax[size];
    // rightMax[i]表示arr[i]右边第一个比自己大的node
    TreeNode* rightMax[size];
    // 辅助栈
    Stack* l_stack = stack_init();
    Stack* r_stack = stack_init();
    // 预处理
    for (int i = 0; i < size; ++i) {
        // 初始化一下
        leftMax[i] = NULL;
        // 处理左边
        deal(l_stack, leftMax, &node_arrays[i], i);
        // 处理右边
        rightMax[size - i - 1] = NULL;
        deal(r_stack, rightMax, &node_arrays[size - i - 1], size - i - 1);
    }
    // 成树
    TreeNode* res = NULL;
    for (int j = 0; j < size; ++j) {
        TreeNode* left = leftMax[j];
        TreeNode* right = rightMax[j];
        // 候选父节点
        TreeNode* parent = NULL;
        if (left == NULL) {
            parent = right;
        }else if (right == NULL) {
            parent = left;
        }else {
            // 选择较小的
            parent = left->value > right->value ? right : left;
        }
        if (parent == NULL) {
            // 自己就是父节点
            res = &node_arrays[j];
            continue;
        }
        // 将自己加入父节点中
        if (parent->left == NULL) {
            parent->left = &node_arrays[j];
        }else {
            parent->right = &node_arrays[j];
        }
    }
    return res;
}



void deal(Stack *pStack, TreeNode *pNode[], TreeNode* node, int i) {
    // 首先循环弹出栈
    while (!stack_is_empty(pStack) && ((TreeNode*)stack_peek(pStack))->value < node->value) {
        stack_poll(pStack);
    }
    // 判断当前值是否应该加入、并设置当前点左边第一个最大值
    if (stack_is_empty(pStack)) {
        // 左边没有最大值
        pNode[i] = NULL;
    }else{
        pNode[i] = (TreeNode*)stack_peek(pStack);
    }
    stack_push(pStack, node);
}


TreeNode* convert2Nodes(const int *arr, int size) {
    TreeNode* treeNodes = calloc(size, sizeof(TreeNode));
    for (int i = 0; i < size; ++i) {
        TreeNode cur = {arr[i], NULL, NULL};
        treeNodes[i] = cur;
    }
    return treeNodes;
}


#ifdef __cplusplus
};
#endif