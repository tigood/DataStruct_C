/*
使用指针实现二叉查找树
*/
#ifndef _BINARY_SEARCH_TREE_PTR_H
#define _BINARY_SEARCH_TREE_PTR_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;

// 将一个二叉查找树清空
// 前置条件：传入一个二叉查找树指针
// 后置条件：清除该二叉查找树中的所有节点
void make_empty(SearchTree *);

// 在一个二叉查找树中查找一个元素
// 前置条件：传入一个指定元素和一个二叉查找树
// 后置条件：如果找到了就返回指定节点，否则返回NULL
Position find(ElementType, SearchTree);

// 在一个二叉查找树中查找最小元素
// 前置条件：传入一个二叉查找树
// 后置条件：返回最小值所在的节点位置
Position find_min(SearchTree);

// 在一个二叉查找树中查找最大元素
// 前置条件：传入一个二叉查找树
// 后置条件：返回该树中最大元素的节点位置
Position find_max(SearchTree);

// 向一个二叉查找树中插入一个元素
// 前置条件：传入一个指定元素和一个二叉查找树
// 后置条件：如果该元素已经在树中，那什么也不做，如果不存在就将该节点插入到适合的位置，并返回该子树
void insert_elem(ElementType, SearchTree *);

// 删除二叉查找树中的一个元素
// 前置条件：传入一个指定元素和一个二叉查找树
// 后置条件：删除该指定元素
void delete_elem(ElementType, SearchTree *);

// 取出当前节点的值
// 前置条件：传入一个节点位置
// 后置条件：返回该节点位置的值
ElementType retrieve(Position);

#endif