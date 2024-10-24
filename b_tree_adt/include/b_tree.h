/*
B树的简单实现
*/
#ifndef _B_TREE_H
#define _B_TREE_H
#define DEGREE 3    // b数的度数，表示树的阶树的一半
#include <stdbool.h>

typedef int KeyValue;  // 键的类型

typedef struct _BTreeNode {
    KeyValue *keys;  // 节点key  最多可以有2 * DEGREE - 1个
    struct _BTreeNode **childrens;  // 孩子指针，最多可以有2 * DEGREE个
    int key_count;  // 节点key的个树
    bool is_leaf;  // 是否是叶子节点, true代表是，false代表否
} BTreeNode;

typedef struct _BTree {
    BTreeNode *root;  // 根节点
    int t;  // 树的度树 即DEGREE
} BTree;

// 创建一个节点 
// 前置条件：传入该节点所在树的度->DEGREE is_leaf表示是否是子节点
// 后置条件：创建一个节点并返回
BTreeNode *btree_create_node(int, bool);

// 节点的销毁
// 前置条件：传入指向节点的指针
// 后置条件：该节点内存被销毁
void btree_dispose_node(BTreeNode *);

// 创建一颗b树
// 前置条件：传入一个指向b树的指针
// 后置条件：创建一个根节点
void btree_create(BTree *, int);

/*
分裂节点：
分裂节点是用于插入节点的，由于插入节点是自上而下的，因此如果找到某个节点已经满了的话，就需要分裂
如果分裂到了该节点，那么说明它的父节点都不是满的
*/
// 前置条件：传入要分裂的节点的父节点，和该父节点的第几个孩子要分裂
// 后置条件：该节点被分裂，结构变更
void btree_split_child(BTree *tree, BTreeNode *node_parent, int i);

#endif