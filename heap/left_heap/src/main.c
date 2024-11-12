#include "../include/left_heap.h"
#include <stdio.h>

int main(void) {
	PriorityQueue q;
	q = init_left_heap();
	q = insert_elem_left_heap(q, 10);
	q = insert_elem_left_heap(q, 12);
	ElementType result = find_min_left_heap(q);
	printf("%d\n", result);

	return 0;
}