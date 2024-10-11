/*
avl树简单实现的头文件
*/
#ifndef _AVL_TREE_H
#define _AVL_TREE_H

struct AvlNode;

typedef int ElementType;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

// 置空
// 前置条件：传入一个avl树
// 后置条件：该avl树被置空
AvlTree make_empty(AvlTree);

// 查找目标节点
// 前置条件：传入一个目标值和一个avl树
// 后置条件：在该树中查找该值，并返回其所在节点
Position find(ElementType, AvlTree);

// 查找最小值
// 前置条件：传入一个指定avl树
// 后置条件：返回该树中的最小值的节点
Position find_min(AvlTree);

// 查找最大值
// 前置条件：传入一个指定的avl树
// 后置条件：返回该树的最大值的节点
Position find_max(AvlTree);

// 插入一个元素
// 前置条件：传入一个目标节点值和一个avl树
// 后置条件：将该值插入在avl树中合理的位置
AvlTree insert_elem(ElementType, AvlTree);

// 删除一个元素
// 前置条件：传入一个目标值和一个avl树
// 后置条件：如果该值存在，删除该节点，否则什么也不做
AvlTree delete_elem(ElementType, AvlTree);

// 获取节点的值
// 前置条件：传入一个树节点
// 后置条件：返回该节点的值
ElementType retrieve(Position);

#endif