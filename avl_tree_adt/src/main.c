#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    AvlTree tree = NULL;
    tree = insert_elem(1, tree);
    tree = insert_elem(2, tree);
    tree = insert_elem(3, tree);
    tree = insert_elem(0, tree);
    tree = insert_elem(10, tree);
    tree = insert_elem_nr(9, tree);
    tree = insert_elem_nr(12, tree);
    printf("当前树的节点: ");
    print_tree(tree);
    printf("\n");


    Position minNode = find_min(tree);
    Position maxNode = find_max(tree);

    if (minNode != NULL) {
        printf("最小的值为：%d\n", retrieve(minNode));
    } else {
        printf("树为空，无法找到最小值！\n");
    }

    if (maxNode != NULL) {
        printf("最大的值为：%d\n", retrieve(maxNode));
    } else {
        printf("树为空，无法找到最大值！\n");
    }

    tree = delete_elem(12, tree);
    tree = delete_elem(0, tree);
    printf("当前树的节点: ");
    print_tree(tree);
    printf("\n");


    minNode = find_min(tree);
    maxNode = find_max(tree);

    if (minNode != NULL) {
        printf("删除后最小的值为：%d\n", retrieve(minNode));
    } else {
        printf("树为空，无法找到最小值！\n");
    }

    if (maxNode != NULL) {
        printf("删除后最大的值为：%d\n", retrieve(maxNode));
    } else {
        printf("树为空，无法找到最大值！\n");
    }

    return 0;
}
