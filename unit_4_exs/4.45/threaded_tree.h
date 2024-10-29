//
// Created by tigood on 2024/10/29.
// 实现的一个线索树结构
//

#ifndef THREADED_TREE_H
#define THREADED_TREE_H
#include <stdbool.h>

typedef int ElementType;
// 线索树结构
typedef struct _TreadedTreeNode {
    ElementType elem;
    struct _TreadedTreeNode *left, *right;
    bool ltag, rtag;  // true表示前驱，false表示是子节点
}TreadedTreeNode, *TreadedTree;

// 向线索树中插入节点 辅助函数
// 前置条件：传入一个指定的线索树，指定的元素，和一个前驱节点
// 后置条件：该节点被插入到该线索树中合适的位置
void treaded_tree_insert_helper(TreadedTree *, ElementType, TreadedTreeNode *);

// 向线索树中插入节点
void treaded_tree_insert(TreadedTree *, const ElementType);

// 查找树中的最小的元素
TreadedTreeNode* threaded_tree_find_min_node(TreadedTree);

// 删除指定的节点
// 前置条件：传入一个指定的线索树，将指定元素删除掉
// 后置条件：将指定的元素删除掉，如果未找到指定的元素，就返回false，如果删除成功返回true
void treaded_tree_delete(TreadedTree *, const ElementType);

// 中序遍历打印线索树
void inorder_traverse(TreadedTree);

#endif //THREADED_TREE_H
