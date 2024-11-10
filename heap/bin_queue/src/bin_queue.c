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

// 合并两个二项队列
BinQueue combin_bin_queues(BinQueue bin_queue_1, BinQueue bin_queue_2) {
	BinTree tree_1, tree_2, carry = NULL;   // tree_1代表H1中的树，而tree_2代表H2中的树，carry代表上一次合并得到的树
	// 判断二项队列的大小
	if (bin_queue_1->curr_size + bin_queue_2->curr_size > MAX_TREE_COUNT) {
		fprintf(stderr, "两个二项队列合并之后长度过长，合并失败！\n");
		exit(EXIT_FAILURE);
	}

	// 将第二个二项队列加入到第一个二项队列中
	bin_queue_1->curr_size += bin_queue_2->curr_size;
	for (int i = 0, j = 1; j <= bin_queue_1->curr_size; i++, j *= 2) {
		tree_1 = bin_queue_1->the_trees[i];
		tree_2 = bin_queue_2->the_trees[i];
		switch (!!tree_1 + 2 * !!tree_2 + 4 * !!carry) {
		case 0:
			// 没有树的情况下
		case 1:
			// 仅仅只有bin_queue_1的树的时候
			break;
		case 2:
			// 仅仅只有bin_queue_2的树的时候
			bin_queue_1->the_trees[i] = tree_2;
			bin_queue_2->the_trees[i] = NULL;
			break;
		case 4:
			// 仅仅只有上一次合成的
			bin_queue_1->the_trees[i] = carry;
			carry = NULL;
		case 3:
			// 有bin_queue_1的树和bin_queue_2的树
			carry = combin_trees(tree_1, tree_2);
			bin_queue_1->the_trees[i] = bin_queue_2->the_trees[i] = NULL;
			break;
		case 5:
			// bin_queue_1和carry
			carry = combin_trees(tree_1, carry);
			bin_queue_1->the_trees[i] = NULL;
			break;
		case 6:
			// bin_queue_2和carry
			carry = combin_trees(tree_2, carry);
			bin_queue_2->the_trees[i] = NULL;
			break;
		case 7:
			// 所有都有
			bin_queue_1->the_trees[i] = carry;
			carry = combin_trees(tree_1, tree_2);
			bin_queue_2->the_trees[i] = NULL;
			break;
		}
	}

	return bin_queue_1;
}