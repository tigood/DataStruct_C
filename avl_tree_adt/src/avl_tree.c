#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

struct AvlNode {
    ElementType elem;
    AvlTree left;
    AvlTree right;
    int height;
};

// 计算节点的高度 static函数，只能在当前源文件中使用
static int height(Position p) {
    if (p == NULL) {
        return -1;
    } else {
        return p->height;
    }
}

// 将avl树置空
AvlTree make_empty(AvlTree avl_tree) {
    // 后序遍历
    if (avl_tree != NULL) {
        make_empty(avl_tree->left);
        make_empty(avl_tree->right);
        free(avl_tree);
    }

    return NULL;
}

// 查找目标节点
Position find(ElementType target, AvlTree avl_tree) {
    if (avl_tree == NULL) {
        printf("未找到指定元素:%d\n", target);
        return NULL;
    }
    else if (target < retrieve(avl_tree))
    {
        // 目标节点小于当前节点的值，那就去左子树中继续找
        return find(target, avl_tree->left);
    }
    else if (target > retrieve(avl_tree))
    {
        // 目标节点大于当前节点的值，那就去右子树中继续找
        return find(target, avl_tree->right);
    }
    else
    {
        // 走到这里就说明是找到了
        return avl_tree;
    }
}

// 查找最小值
Position find_min(AvlTree avl_tree) {
    if (avl_tree == NULL) {
        // 非空检测
        return NULL;
    } else if (avl_tree->left == NULL) {
        return avl_tree;
    } else {
        return find_min(avl_tree->left);
    }
}