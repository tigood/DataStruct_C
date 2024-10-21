#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

// 生成高度为H的节点最少的avl树  时间复杂度为O(2^H) 空间复杂度为O(H)
AvlTree generate_avl_tree_min_nodes(int height) {
    if (height < 0) {
        return NULL;
    }

    AvlTree node = (AvlTree)malloc(sizeof(struct AvlNode));
    if (node == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    node->height = height;
    node->left = generate_avl_tree_min_nodes(height - 1);
    node->right = generate_avl_tree_min_nodes(height - 2);
    node->elem = node->left ? node->left->elem + 1 : 1;

    return node;
}

// 打印树
void print_avl_tree(AvlTree tree) {
    if (tree != NULL) {
        print_avl_tree(tree->left);
        printf("%d  ", tree->elem);
        print_avl_tree(tree->right);
    }
}

int main(void) {
    int height;
    AvlTree tree;
    printf("请输入您要生成最少节点的avl树的高度：\n");
    scanf("%d", &height);
    tree = generate_avl_tree_min_nodes(height);
    print_avl_tree(tree);
    printf("\n");

    return 0;
}