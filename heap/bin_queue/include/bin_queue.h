/*
二项队列实现的头文件
 */
#ifndef BIN_QUEUE_H
#define BIN_QUEUE_H
#define MAX_TREE_COUNT 10
#include <stdbool.h>

struct BinNode;  // 节点
struct Collection;  // 堆序树集合
typedef int ElementType;  // 元素
typedef struct BinNode *Position, *BinTree;   // 节点
typedef struct Collection *BinQueue;

struct BinNode {
	ElementType elem;
	Position left_child;   // 最左边的节点
	Position next_sibling;   // 下一个兄弟节点
};

struct Collection {
	int curr_size;
	BinTree the_trees[MAX_TREE_COUNT];   // 二项队列的堆序树集合
};

// 初始化一个二项队列
BinQueue init_bin_queue(void);

// 判断二项队列是否为空
bool is_empty_bin_queue(BinQueue);

// 合并两个同样大小的树
BinTree combin_trees(BinTree tree_1, BinTree tree_2);

// 合并两个二项队列
BinQueue combin_bin_queues(BinQueue bin_queue_1, BinQueue bin_queue_2);

// 删除并返回堆中最小元素
ElementType delete_min_bin_queue(BinQueue bin_queue);
#endif