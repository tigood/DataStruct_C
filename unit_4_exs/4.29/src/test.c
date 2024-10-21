#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 随机生成一个二叉查找树
SearchTree generateRandomBST(int n) {
    // 为节点开辟空间
    ElementType *keys = (ElementType *)malloc(n * sizeof(ElementType));

    // 检测空间是否开辟成功
    if (keys == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 对这个数组赋初值
    for (int i = 0; i < n; i++) {
        keys[i] = i + 1;
    }

    // 随机打乱数组中元素的数据
    for (int i = n - 1; i >= 0; i--) {
        int j = rand() % (i + 1);
        int temp = keys[i];
        keys[i] = keys[j];
        keys[j] = temp;
    }

    // 创建一颗树
    SearchTree tree = NULL;
    for (int i = 0; i < n; i++) {
        tree = insert_elem(keys[i], tree);
    }

    free(keys);
    return tree;
}

// 打印这棵树
void printTree(SearchTree tree) {
    if (tree != NULL) {
        printTree(tree->left);
        printf("%d  ", tree->elem);
        printTree(tree->right);
    }
}

int main(void) {
    int n;
    printf("请输入要生成几个节点的二叉查找树：\n");
    scanf("%d", &n);
    SearchTree tree;

    if (n > 0) {
        tree = generateRandomBST(n);
    } else {
        printf("数量输入不正确!\n");
    }

    printf("树的内容如下：\n");
    printTree(tree);
    printf("\n");

    return 0;
}