//
// Created by tigood on 2024/10/28.
// 基本树结构的实现
//

#ifndef TREE_H
#define TREE_H
// 树的结构实现
typedef char ElementType;  // 存储的元素类型
typedef struct _TreeNode {
    ElementType elem;  // 节点的值
    struct _TreeNode *first_child;  // 当前节点的第一个子结点
    struct _TreeNode *next_sibling;  // 下一个兄弟节点
} TreeNode, *Tree;

// 打印一颗树
void print_tree(Tree tree);

#endif //TREE_H
