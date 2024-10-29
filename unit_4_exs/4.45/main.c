#include <stdio.h>
#include "threaded_tree.h"

int main(void) {
    TreadedTree tree = NULL;

    // 插入节点
    treaded_tree_insert(&tree, 20);
    treaded_tree_insert(&tree, 10);
    treaded_tree_insert(&tree, 30);
    treaded_tree_insert(&tree, 5);
    treaded_tree_insert(&tree, 15);
    treaded_tree_insert(&tree, 25);
    treaded_tree_insert(&tree, 35);
    printf("\n");

    printf("线索树的线索遍历：");
    inorder_traverse(tree);
    printf("\n");

    printf("删除节点 15:\n");
    treaded_tree_delete(&tree, 15);
    printf("删除后线索树的线索遍历：");
    inorder_traverse(tree);
    printf("\n");

    return 0;
}
