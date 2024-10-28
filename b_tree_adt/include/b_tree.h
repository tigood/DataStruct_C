/*
Created by tigood on 2024/10/27.
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
void btree_split_child(const BTree *tree, BTreeNode *node_parent, int i);

/*
树根节点没有满的时候插入  （辅助函数）
*/
// 前置条件：传入要插入的树， 传入要插入的节点，传入要插入的节点的key
// 后置条件：该节点被成功的插入
void btree_insert_nofull(BTree *tree, BTreeNode *target_node, KeyValue k_val);

/*
节点的插入
*/
// 前置条件：传入要插入的树，传入要插入的节点的值
// 后置条件：该节点被成功的插入，b树结构依旧稳定
void btree_insert(BTree *tree, KeyValue k_val);

/*
中序遍历该子树
*/
// 前置条件：传入一个树节点
// 后值条件：将该树进行中序遍历
void btree_traverse(const BTreeNode *);

// 打印一个b树
// 前置条件：传入要打印的树，和起始节点和当前层数
void btree_print(BTree *, BTreeNode *, int layer);

/*
 *二分查找法查找元素
 *用途：在找到目标节点之后，在它的keys中查找元素，keys是按照从小到大的顺序排列的
 *前置条件：传入目标节点，和指定的元素值
 *后置条件：如果找到该节点，返回它的值
 */
int btree_binary_search(const BTreeNode *, KeyValue);

// 节点的合并
// 前置条件：传入指定的b树，和要合并的节点的父节点，和指定键的下标
// 后置条件：将该节点下沉并和两个子节点合并 新节点即{childs{index},key{index},childs{index + 1}}
void btree_merge(BTree *, BTreeNode **, int);

// 删除的节点函数的辅助函数
// 前置条件：传入指定的树，起始节点，和目标值
// 后置条件：如果找到目标值，就删除
void btree_delete_key_recu(BTree *, BTreeNode *, KeyValue);

// 删除指定节点
// 前置条件：传入指定的树，和目标节点的值
// 后置条件：如果找到该节点，就删除
bool btree_delete_key(BTree *, KeyValue);

#endif
