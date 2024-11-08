#ifndef LEFT_HEAP_H
#define LEFT_HEAP_H
#include <stdbool.h>

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PriorityQueue;

struct TreeNode {
	ElementType elem;  // 节点值
	PriorityQueue left;  // 左子堆
	PriorityQueue right;  // 右子堆
	int npl;  // 零路径长
};

// 初始化一个左式堆
PriorityQueue init_left_heap(void);

// 返回左式堆中的最小值
ElementType find_min_left_heap(PriorityQueue left_heap);

// 判断左式堆是否为空
bool is_empty_left_heap(PriorityQueue left_heap);

// 合并两个左式堆
PriorityQueue merge_left_heap(PriorityQueue left_heap_1, PriorityQueue left_heap_2);

// 通过宏定义实现与之前的二叉堆一样效果的插入和删除
#define insert_elem_left_heap_h(X, H) (H = insert_elem_left_heap((X), H))
#define delete_elem_left_heap_h(H) (H = delete_elem_left_heap(H))

// 插入方法的辅助方法，返回新的堆
PriorityQueue insert_elem_left_heap(PriorityQueue left_heap, ElementType elem);

// 删除方法的辅助函数，返回删除后的新堆
PriorityQueue delete_helper_left_heap(PriorityQueue left_heap);

#endif