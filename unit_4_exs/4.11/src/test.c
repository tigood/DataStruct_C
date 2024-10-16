#include "binary_search_tree_ptr.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 创建树
    SearchTree search_tree = NULL;
    insert_elem(3, &search_tree);
    insert_elem(10, &search_tree);
    insert_elem(2, &search_tree);
    insert_elem(4, &search_tree);

    printf("其中最小的元素是：%d\n", retrieve(find_min(search_tree)));
    printf("其中最大的元素是：%d\n", retrieve(find_max(search_tree)));

    delete_elem(10, &search_tree);
    printf("其中最大的元素是：%d\n", retrieve(find_max(search_tree)));

    make_empty(&search_tree);

    return 0;
}