#include "../include/left_heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 初始化一个左式堆
PriorityQueue init_left_heap(void) {
	// 象征性的返回一个空值
	return NULL;
}

// 返回左式堆中的最小值
ElementType find_min_left_heap(PriorityQueue left_heap) {
	if (!left_heap) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return left_heap->elem;
}

// 判断左式堆是否为空
bool is_empty_left_heap(PriorityQueue left_heap) {
	return left_heap ? true : false;
}

// 交换一个堆的左右节点
static void swap_children(PriorityQueue left_heap) {
	PriorityQueue temp = left_heap->left;
	left_heap->left = left_heap->right;
	left_heap->right = temp;
}

// 合并堆的辅助函数
// 第一个堆的最小元素是最小的，将第二个堆加到第一个下
static PriorityQueue merge_left_heap_helper(PriorityQueue left_heap_1, PriorityQueue left_heap_2) {
	if (!left_heap_1->left)
		left_heap_1->left = left_heap_2;
	else {
		left_heap_1->right = merge_left_heap(left_heap_1->right, left_heap_2);
		if (left_heap_1->left->npl < left_heap_1->right->npl)
			swap_children(left_heap_1);

		left_heap_1->npl = left_heap_1->right->npl + 1;
	}

	return left_heap_1;
}

// 合并两个左式堆
PriorityQueue merge_left_heap(PriorityQueue left_heap_1, PriorityQueue left_heap_2) {
	if (!left_heap_1)
		return left_heap_2;
	if (!left_heap_2)
		return left_heap_1;
	if (left_heap_1->elem < left_heap_2->elem)
		return merge_left_heap_helper(left_heap_1, left_heap_2);
	else
		return merge_left_heap_helper(left_heap_2, left_heap_1);
}

// 插入方法的辅助方法，返回新的堆
PriorityQueue insert_elem_left_heap(PriorityQueue left_heap, ElementType elem) {
	// 将插入看作，一个堆和一个单一节点的堆的合并
	PriorityQueue new_node = malloc(sizeof(struct TreeNode));
	if (!new_node) {
		fprintf(stderr, "空间开辟错误！\n");
		exit(EXIT_FAILURE);
	}

	// 初始化新节点
	new_node->elem = elem;
	new_node->left = new_node->right = NULL;
	new_node->npl = 0;

	// 插入
	left_heap = merge_left_heap(left_heap, new_node);

	return left_heap;
}

PriorityQueue delete_elem_left_heap(PriorityQueue left_heap) {
	if (is_empty_left_heap(left_heap)) {
		fprintf(stderr, "左式堆为空删除失败！\n");
		exit(EXIT_FAILURE);
	}

	PriorityQueue left_child = left_heap->left;
	PriorityQueue right_child = left_heap->right;
	// 释放被删除的节点
	free(left_heap);
	return merge_left_heap(left_child, right_child);
}