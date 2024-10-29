//
// Created by tigood on 2024/10/29.
// 有部分bug未修改
//
#include "threaded_tree.h"
#include <stdio.h>
#include <stdlib.h>

// 向线索树中插入节点 辅助函数
void treaded_tree_insert_helper(TreadedTree *tree, const ElementType elem, TreadedTreeNode *p_pre_node) {
    if (*tree == NULL) {
        // 创建新节点
        TreadedTreeNode *new_node = malloc(sizeof(TreadedTreeNode));
        if (!new_node) {
            fprintf(stderr, "内存不足，空间开辟失败！\n");
            exit(EXIT_FAILURE);
        }
        new_node->elem = elem;
        new_node->left = NULL; // 初始化左指针
        new_node->right = NULL; // 初始化右指针
        new_node->ltag = true;  // 左指针为线索
        new_node->rtag = true;   // 右指针为线索

        *tree = new_node; // 将新节点赋给当前树节点

        // 更新前驱节点的后驱指针
        if (p_pre_node != NULL) {
            p_pre_node->right = new_node; // 设置前驱的后驱指针
            p_pre_node->rtag = false;      // 前驱的右指针不再是线索
            new_node->left = p_pre_node;   // 新节点的左指针指向前驱节点
        }

        printf("节点 %d 插入成功！\n", elem);
    } else if (elem < (*tree)->elem) {
        // 插入左子树
        if ((*tree)->ltag) {
            // 如果左指针是线索，则插入新节点
            TreadedTreeNode *new_node = malloc(sizeof(TreadedTreeNode));
            if (!new_node) {
                fprintf(stderr, "内存不足，空间开辟失败！\n");
                exit(EXIT_FAILURE);
            }
            new_node->elem = elem;
            printf("节点 %d 插入成功！\n", elem);
            new_node->left = (*tree)->left; // 新节点的左指针指向当前节点的左指针
            new_node->ltag = true;          // 新节点的左指针为线索
            new_node->right = *tree;        // 新节点的右指针指向当前节点
            new_node->rtag = true;          // 新节点的右指针为线索

            // 更新当前节点的左指针
            (*tree)->left = new_node;       // 当前节点的左指针指向新节点
            (*tree)->ltag = false;          // 当前节点的左指针不再是线索

            // 更新前驱节点的后驱指针
            if (new_node->left != NULL) {
                new_node->left->right = new_node; // 更新前驱节点的后驱指针
            }
        } else {
            // 递归插入到左子树
            treaded_tree_insert_helper(&(*tree)->left, elem, *tree);
        }
    } else if (elem > (*tree)->elem) {
        // 插入右子树
        if ((*tree)->rtag) {
            // 如果右指针是线索，则插入新节点
            TreadedTreeNode *new_node = malloc(sizeof(TreadedTreeNode));
            if (!new_node) {
                fprintf(stderr, "内存不足，空间开辟失败！\n");
                exit(EXIT_FAILURE);
            }
            new_node->elem = elem;
            printf("节点 %d 插入成功！\n", elem);
            new_node->left = *tree;         // 新节点的左指针指向当前节点
            new_node->ltag = true;          // 新节点的左指针为线索
            new_node->right = (*tree)->right; // 新节点的右指针指向当前节点的右子节点
            new_node->rtag = true;          // 新节点的右指针为线索

            // 更新当前节点的右指针
            (*tree)->right = new_node;      // 当前节点的右指针指向新节点
            (*tree)->rtag = false;          // 当前节点的右指针不再是线索

            // 更新前驱节点的前驱指针
            if (new_node->right != NULL) {
                new_node->right->left = new_node; // 更新前驱节点的前驱指针
            }
        } else {
            // 递归插入到右子树
            treaded_tree_insert_helper(&(*tree)->right, elem, *tree);
        }
    } else {
        printf("不能插入重复的节点 %d!\n", elem);
    }
}

// 向线索树中插入节点
void treaded_tree_insert(TreadedTree *tree, const ElementType elem) {
    treaded_tree_insert_helper(tree, elem, NULL);
}

// 查找最小节点
TreadedTreeNode* threaded_tree_find_min_node(TreadedTreeNode* node) {
    while (node && !node->ltag) { // 一直向左遍历
        node = node->left;
    }
    return node; // 返回找到的最小值节点
}

// 删除指定的节点
// 从线索树中删除节点 辅助函数
void treaded_tree_delete(TreadedTree *tree, const ElementType elem) {
    if (*tree == NULL) {
        printf("节点 %d 不存在！\n", elem);
        return;
    }

    TreadedTreeNode *current = *tree;
    TreadedTreeNode *parent = NULL;
    bool is_left_child = false;

    // 查找节点
    while (current != NULL) {
        if (elem < current->elem) {
            parent = current;
            current = current->left;
            is_left_child = true;
        } else if (elem > current->elem) {
            parent = current;
            current = current->right;
            is_left_child = false;
        } else {
            break; // 找到节点
        }
    }

    if (current == NULL) {
        printf("节点 %d 不存在！\n", elem);
        return;
    }

    // 删除节点
    if (current->ltag && current->rtag) {
        // 当前节点是叶子节点
        if (parent == NULL) {
            *tree = NULL; // 删除根节点
        } else {
            if (is_left_child) {
                parent->left = NULL;
                parent->ltag = true; // 更新左指针为线索
            } else {
                parent->right = NULL;
                parent->rtag = true; // 更新右指针为线索
            }
        }
    } else if (!current->ltag && current->rtag) {
        // 当前节点只有左子树
        if (parent == NULL) {
            *tree = current->left; // 更新根节点
        } else {
            if (is_left_child) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
        }
    } else if (current->ltag && !current->rtag) {
        // 当前节点只有右子树
        if (parent == NULL) {
            *tree = current->right; // 更新根节点
        } else {
            if (is_left_child) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
        }
    } else {
        // 当前节点有两个子树，找到右子树的最小节点进行替换
        TreadedTreeNode *successor = current->right;
        TreadedTreeNode *successor_parent = current;

        while (successor != NULL && !successor->ltag) {
            successor_parent = successor;
            successor = successor->left;
        }

        // 替换当前节点的值
        current->elem = successor->elem;

        // 删除后继节点
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
            successor_parent->ltag = true; // 更新前驱节点的左指针为线索
        } else {
            successor_parent->right = successor->right;
            successor_parent->rtag = true; // 更新前驱节点的右指针为线索
        }

        current = successor; // 更新当前节点
    }

    free(current);
    printf("节点 %d 删除成功！\n", elem);
}


void inorder_traverse(TreadedTree root) {
    TreadedTreeNode *current = root;

    // 找到最左节点
    while (current && !current->ltag) {
        current = current->left;
    }

    while (current != NULL) {
        // 访问当前节点
        printf("%d ", current->elem);

        // 如果当前节点的右指针是线索，访问后继
        if (current->rtag) {
            current = current->right; // 移动到后继
        } else {
            // 否则，找到当前节点右子树的最左节点
            current = current->right;
            while (current && !current->ltag) {
                current = current->left;
            }
        }
    }
    printf("\n");
}
