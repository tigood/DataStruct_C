#include "../include/b_tree.h"
#include <stdio.h>

int main(void) {
    // 创建一个b树
    BTree tree;
    btree_create(&tree, 3);

    btree_insert(&tree, 2);
    btree_insert(&tree, 11);
    btree_insert(&tree, 1);
    btree_insert(&tree, -4);
    btree_insert(&tree, 14);
    btree_insert(&tree, 20);
    btree_insert(&tree, -7);
    btree_insert(&tree, 12);
    btree_insert(&tree, 4);
    btree_insert(&tree, 0);

    btree_traverse(tree.root);
    printf("\n");
    // btree_print(&tree, tree.root, tree.root->is_leaf);

    // 删除测试
    btree_delete_key(&tree, 12);
    btree_delete_key(&tree, -7);
    printf("删除了节点12和-7\n");
    btree_traverse(tree.root);
    printf("\n");
    // btree_print(&tree, tree.root, tree.root->is_leaf);

    return 0;
}