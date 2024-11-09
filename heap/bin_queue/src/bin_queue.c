#include "../include/bin_queue.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化一个二项队列
BinQueue init_bin_queue(void) {
	BinQueue queue = malloc(sizeof(struct Collection));
	if (!queue) {
		fprintf(stderr, "空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}
	queue->curr_size = 0;

	return queue;
}

// 合并两个同样大小的树
BinTree combin_trees(BinTree tree_1, BinTree tree_2) {
	if (!tree_1 || !tree_2) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}
	
	if (tree_1->elem > tree_2->elem)
		return combin_trees(tree_2, tree_1);

	// 更新两个树的指针
	tree_2->next_sibling = tree_1->left_child;
	tree_1->left_child = tree_2;
	return tree_1;
}