#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

AvlTree generate_avl_tree(int height, ElementType *last_node_val) {
    if (height < 0) {
        return NULL;
    }
    AvlTree root = NULL;

    root = (AvlTree)malloc(sizeof(struct AvlNode));
    if (root == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    root->height = height;
    root->left = generate_avl_tree(height - 1, last_node_val);
    root->elem = ++(*last_node_val);
    root->right = generate_avl_tree(height - 1, last_node_val);

    return root;
}

AvlTree max_avl_tree(int height) {
    ElementType node_val = 0;
    return generate_avl_tree(height, &node_val);
}

void print_avl_tree(AvlTree tree) {
    if (tree != NULL) {
        print_avl_tree(tree->left);
        printf("%d  ", tree->elem);
        print_avl_tree(tree->right);
    }
}

int main(void) {
    int n;
    AvlTree tree = NULL;
    printf("请输入你要是生成树的高度：\n");
    scanf("%d", &n);
    if (n < 0) {
        printf("输入的高度不合理！\n");
        return -1;
    }

    tree = max_avl_tree(n);
    printf("树的内容如下：\n");
    print_avl_tree(tree);
    printf("\n");

    return 0;
}