#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

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