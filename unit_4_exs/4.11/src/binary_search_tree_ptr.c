#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree_ptr.h"

// 二叉查找树节点的实现
struct TreeNode {
    ElementType elem;
    SearchTree left;
    SearchTree right;
};

// 取出当前节点的值
ElementType retrieve(Position node) {
    if (node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    return node->elem;
}

// 将一个二叉查找树清空
void make_empty(SearchTree *p_search_tree) {
    if (p_search_tree != NULL && *p_search_tree != NULL) {
        make_empty(&(*p_search_tree)->left);
        make_empty(&(*p_search_tree)->right);
        free(*p_search_tree);
    }

    // 将树指针置为空
    *p_search_tree = NULL;
}

// 在一个二叉查找树中查找一个元素
// 这是一个尾递归实现，可以优化为迭代实现，即用for实现
Position find(ElementType elem, SearchTree search_tree) {
    if (search_tree == NULL) {
        // 未查找到
        return NULL;
    } else if (elem < retrieve(search_tree)) {
        return find(elem, search_tree->left);
    } else if (elem > retrieve(search_tree)) {
        return find(elem, search_tree->right);
    } else {
        return search_tree;
    }
}

// 在一个二叉查找树中查找最小元素
Position find_min(SearchTree search_tree) {
    if (search_tree == NULL)
        return NULL;
    
    if (search_tree->left == NULL)
        return search_tree;
    else
        return find_min(search_tree->left);
}

// 在一个二叉查找树中查找最大元素
Position find_max(SearchTree search_tree) {
    if (search_tree == NULL)
        return NULL;
    
    if (search_tree->right == NULL)
        return search_tree;
    else
        return find_max(search_tree->right);
}

// 向一个二叉查找树中插入一个元素
void insert_elem(ElementType elem, SearchTree *p_search_tree) {
    // 参数合法性检测
    if (p_search_tree == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    // 开始插入元素逻辑
    if (*p_search_tree == NULL) {
        // 说明找到了指定位置，创建节点
        *p_search_tree = (SearchTree)malloc(sizeof(struct TreeNode));
        // 判断空间是否开辟成功
        if (!(*p_search_tree)) {
            fprintf(stderr, "空间开辟失败！\n");
            exit(EXIT_FAILURE);
        }
        // 初始化该节点
        (*p_search_tree)->elem = elem;
        (*p_search_tree)->left = (*p_search_tree)->right = NULL;
    } 
    else if (elem < retrieve(*p_search_tree))
        insert_elem(elem, &(*p_search_tree)->left);
    else
        insert_elem(elem, &(*p_search_tree)->right);
}

// 删除二叉查找树中的一个元素
void delete_elem(ElementType target, SearchTree *p_search_tree) {
    // 检测参数合法性
    if (!p_search_tree) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    // 定义一个临时变量
    Position tempPos;
    if (!(*p_search_tree)) {
        printf("未找到指定元素，删除失败！\n");
        return;
    }
    if (target < retrieve(*p_search_tree))
        // 如果目标元素比当前节点值小，去左子树找
        delete_elem(target, &(*p_search_tree)->left);
    else if (target > retrieve(*p_search_tree))
        delete_elem(target, &(*p_search_tree)->right);
    else if ((*p_search_tree)->left && (*p_search_tree)->right) {
        // 走到这里说明找到了，并且有两个节点
        tempPos = find_min((*p_search_tree)->right);
        // 用这个值代替当前节点的值
        (*p_search_tree)->elem = retrieve(tempPos);
        // 删除找到的子结点
        delete_elem(retrieve(*p_search_tree), &(*p_search_tree)->right);
    }
    else
    {
        // 走到这里说明只有一个子节点或者没有子节点
        tempPos = *p_search_tree;
        if ((*p_search_tree)->left)
            *p_search_tree = (*p_search_tree)->left;
        else
            *p_search_tree = (*p_search_tree)->right;
        
        // 释放节点空间
        free(tempPos);
    }
}