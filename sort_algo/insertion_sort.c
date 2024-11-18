/*
插入算法的实现
算法思路：
	外层循环从第二个元素开始遍历，通过内层循环寻找到该外层循环遍历到的元素适合的位置，然后将该元素插入到该指定位置
	即，对于每个元素，将其与之前的元素逐一比较，来找到合适的位置  (7 * 10 + 4) * 3
算法时间复杂度：O(n^2)
 */
#include "sort_algo.h"

void insertion_sort(ElementType arr[], int len) {
	ElementType temp;
	int i, j;

	for (i = 1; i < len; i++) {
		temp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > temp; j--) 
			arr[j] = arr[j - 1];
		arr[j] = temp;
	}
}