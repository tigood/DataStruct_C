/*
二叉查找树测试代码
*/
#include <stdio.h>
#include "binary_search_tree.h"

int main(void) {
    SearchTree tree = NULL;
    tree = make_empty(tree);
    tree = insert_elem(1, tree);
    tree = insert_elem(3, tree);
    tree = insert_elem(6, tree);
    printf("树中最小的元素为：%d\n", retrieve(find_min(tree)));
    printf("树中最大的元素为：%d\n", retrieve(find_max(tree)));

    return 0;
}