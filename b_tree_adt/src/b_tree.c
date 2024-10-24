#include "../include/b_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 创建一个节点 
// 前置条件：传入该节点所在树的度->DEGREE is_leaf表示是否是子节点
// 后置条件：创建一个节点并返回
BTreeNode *btree_create_node(int t, bool is_leaf) {
    // 创建节点
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    // 判断空间是否开辟成功
    if (!node) {
        fprintf(stderr, "节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 对属性进行初始化
    node->is_leaf = is_leaf;
    node->keys = (KeyValue *)calloc(2 * t - 1, sizeof(KeyValue));
    node->childrens = (BTreeNode **)calloc(2 * t, sizeof(BTreeNode *));
    node->key_count = 0; // 当前不存在key

    return node;
}

// 节点的销毁
// 前置条件：传入指向节点的指针
// 后置条件：该节点内存被销毁
void btree_dispose_node(BTreeNode *node) {
    // 检测参数合法性
    if (node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    free(node->childrens);
    free(node->keys);
    free(node);
}

// 创建一颗b树
// 前置条件：传入一个指向b树的指针
// 后置条件：创建一个根节点
void btree_create(BTree *tree, int t) {
    if (tree == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    tree->t = t;
    tree->root = btree_create_node(t, true);
}

/*
分裂节点：
分裂节点是用于插入节点的，由于插入节点是自上而下的，因此如果找到某个节点已经满了的话，就需要分裂
如果分裂到了该节点，那么说明它的父节点都不是满的
*/
void btree_split_child(BTree *tree, BTreeNode *target_node_parent, int i) {
    // 检测参数合法性
    if (tree == NULL || target_node_parent == NULL) {
        fprintf(stderr, "参数传递不合法！\n");
        exit(EXIT_FAILURE);
    }

    int t = tree->t;  // 记录当前树的度数

    // 找到要分裂的节点
    BTreeNode *target_node = target_node_parent->childrens[i];
    // 创建一个新的节点，存储分裂之后的后半部分元素
    BTreeNode *new_node = btree_create_node(t, target_node->is_leaf);

    new_node->key_count = t - 1;  // 设置该新节点的键数
    for (int j = 0; j < t - 1; j++) {
        new_node->keys[j] = target_node->keys[j + t];
    }
    // 如果不是叶子节点，那么还需要将该节点的子节点们也都放到新的节点中
    if (!target_node->is_leaf) {
        for (int j = 0; j < t - 1; j++) {
            new_node->childrens[j] = target_node->childrens[j + t];
        }
    }
}