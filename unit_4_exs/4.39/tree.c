//
// Created by tigood on 2024/10/28.
//
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// 打印一颗树  使用循环实现
void print_tree(Tree tree) {
    // 参数合法性检测
    if (tree == NULL) {
        printf("参数传递失败！\n");
        exit(EXIT_FAILURE);
    }

    TreeNode *curr_node = tree;
    int level = 0;
    while (curr_node != NULL) {
        level++;
        printf("这是第%d层：", level);
        TreeNode *temp_node = curr_node;
        while (temp_node) {
            // 打印其余的兄弟节点
            printf("%c ", temp_node->elem);
            temp_node = temp_node->next_sibling;
        }
        printf("\n");
        curr_node = curr_node->first_child;
    }
}
