#include "sort_algo.h"
#include <stdio.h>

int main(void) {
	ElementType arr[] = {5, 3, 2, 4, 7, 9};
	for (int i = 0; i < 6; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
	insertion_sort(arr, 6);
	for (int i = 0; i < 6; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");

	return 0;
}