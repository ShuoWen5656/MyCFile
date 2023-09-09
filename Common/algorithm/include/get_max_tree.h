//
// Created by admin on 2023/9/9.
//

/**
 * 问题：构造数组的MaxTree
 */
#ifndef MYCPROJECT_GET_MAX_TREE_H
#define MYCPROJECT_GET_MAX_TREE_H

#endif //MYCPROJECT_GET_MAX_TREE_H



/*****************************************************************************************************
 * 由于C++编译器支持重载，函数名称会做一些处理，而在c中仅是简单函数名，这里定义为了告诉c++编译器按照C语言的方式编译即可*
 *****************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct TreeNode TreeNode;
/**
 * 树结构（只存int）
 */
struct TreeNode{
    int value;

    TreeNode* left;

    TreeNode* right;

};


/**
 * 获取最大树
 * @return
 */
TreeNode* getMaxNode(int arr[], int size);



#ifdef __cplusplus
};
#endif