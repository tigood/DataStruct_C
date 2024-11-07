#include "../include/bin_heap.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化一个优先队列（即二叉堆）
PriorityQueue init_priority_queue(int max_elems) {
	PriorityQueue q;

	// 大小参数合法性检测
	if (max_elems < MINSIZE) {
		printf("堆的长度太小!\n");
		return NULL;
	}

	// 开辟空间
	q = malloc(sizeof(struct HeapStruct));
	if (!q) {
		fprintf(stderr, "二叉堆空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}

	// 为堆中元素开辟空间
	q->elements = malloc((max_elems + 1) * sizeof(ElementType));
	if (!(q->elements)) {
		fprintf(stderr, "空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}

	q->capacity = max_elems;
	q->size = 0;
	q->elements[0] = MINDATA;

	return q;
}

// 向一个优先队列中插入一个元素
void insert_elem_priority_queue(PriorityQueue priority_queue, ElementType elem) {
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	if (is_full_priority_queue(priority_queue)) {
		fprintf(stderr, "堆已经满了，插入失败！\n");
		exit(EXIT_FAILURE);
	}

    int i;
    // 在堆的最后开辟一个新的空间，然后将新值放到这个空间空间中，然后将该值与父节点比较，如果该值较小，就将该值上移，父节点下沉
    // 直到到找一个父节点小于当前节点的值，这就是该元素该存在的位置，然后直接赋值
	for (i = ++priority_queue->size; priority_queue->elements[i / 2] > elem; i /= 2) {
		priority_queue->elements[i] = priority_queue->elements[i / 2];
	}
	priority_queue->elements[i] = elem;
}

// 删除这个二叉堆中的最小值，并返回该值
ElementType delete_min_priority_queue(PriorityQueue priority_queue) {
	// 检测参数合法性
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	// 思路：删除了顶部的值之后，为了维护堆的性质，将左右节点中的较小值上沉到该位置，然后直到最后一层，将最后一个元素弥补到空穴中
	int curr, child;
	ElementType min_elem, last_elem;

	// 判断当前堆是否为空，如果为空就删除失败
	if (is_empty_priority_queue(priority_queue)) {
		fprintf(stderr, "二叉堆为空，删除失败！\n");
		exit(EXIT_FAILURE);
	}

	min_elem = priority_queue->elements[1];   // 其中下标为0的元素不是真实元素，而是一个标记值
	last_elem = priority_queue->elements[priority_queue->size--];

	for (curr = 1; curr * 2 <= priority_queue->size; curr = child) {
		child = curr * 2;
		if (child != priority_queue->size && priority_queue->elements[child + 1] < priority_queue->elements[child]) {
			child++;
		}
		// 上滤
		if (last_elem > priority_queue->elements[child])
			priority_queue->elements[curr] = priority_queue->elements[child];
		else
			break;
	}

	priority_queue->elements[curr] = last_elem;

	// 返回最小值
	return min_elem;
}

// 找到二叉堆中的最小值
ElementType find_min_priority_queue(PriorityQueue priority_queue) {
	// 参数合法性检测
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	if (is_empty_priority_queue(priority_queue)) {
		fprintf(stderr, "堆为空没有最小值！\n");
		exit(EXIT_FAILURE);
	}

	return priority_queue->elements[1];
}

// 判断二叉堆是否为空
bool is_empty_priority_queue(PriorityQueue priority_queue) {
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return priority_queue->size == 0;
}

// 判断二叉堆是否为满
bool is_full_priority_queue(PriorityQueue priority_queue) {
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return priority_queue->size == priority_queue->capacity - 1;  // 由于下标为0的位置存储的是标志位
}

// 清空一个优先队列
void empty_priority_queue(PriorityQueue priority_queue) {
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	if (!is_empty_priority_queue(priority_queue)) {
		for (int i = 1; i < priority_queue->size; i++) 
			priority_queue->elements[i] = 0;
		priority_queue->size = 0;
	}
}

// 销毁一个优先队列
void destroy_priority_queue(PriorityQueue priority_queue) {
	if (!priority_queue) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	empty_priority_queue(priority_queue);
	free(priority_queue->elements);
	free(priority_queue);
}