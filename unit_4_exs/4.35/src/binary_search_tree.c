#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

// 将一个二叉查树清空
SearchTree make_empty(SearchTree search_tree) {
    // 首先对子树进行非空判断，防止进入左右子树的无限转换
    if (search_tree != NULL) {
        // 后序遍历
        make_empty(search_tree->left);
        make_empty(search_tree->right);
        free(search_tree);
    }

    return search_tree;
}

// 在一个二叉查找树中查找一个元素
Position find(ElementType target, SearchTree search_tree) {
    // 首先对二叉查找树进行非空判断
    if (search_tree == NULL)
        return NULL;
    else if (search_tree->elem < target)
    {
        // 如果当前节点值小于目标值，那么就继续查当前节点的右子树
        return find(target, search_tree->right);
    }
    else if (search_tree->elem > target)
    {
        // 如果当前节点值大于目标值，那么就继续查当前节点的左子树
        return find(target, search_tree->left);
    }
    else
    {
        // 查到就返回当前的点
        return search_tree;
    }
}

// 在一个二叉查找树中查找最小元素
Position find_min(SearchTree search_tree) {
    if (search_tree == NULL) {
        // 子树非空检测
        return NULL;
    } else if (search_tree->left == NULL) {
        // 如果没有左子树了，说明当前节点值是最小的
        return search_tree;
    } else {
        // 走到这里就是还有左子树，继续查找
        return find_min(search_tree->left);
    }
}

// 在一个二叉查找树中查找最大元素
Position find_max(SearchTree search_tree) {
    // 这个使用循环实现
    if (search_tree != NULL) {
        while (search_tree->right != NULL)
            search_tree = search_tree->right;
    }

    return search_tree;
}

// 向一个二叉查找树中插入一个元素
SearchTree insert_elem(ElementType elem, SearchTree search_tree) {
    if (search_tree == NULL) {
        // 创建一个新节点
        search_tree = (SearchTree)malloc(sizeof(struct TreeNode));
        // 判断是否创建成功
        if (!search_tree) {
            fprintf(stderr, "节点空间开辟失败！\n");
            exit(EXIT_FAILURE);
        }
        
        // 初始化节点
        search_tree->elem = elem;
        search_tree->right = search_tree->left = NULL;
    } else if (elem < search_tree->elem) {
        // 如果指定元素小于当前节点的元素值，就向该树的左子树移动
        search_tree->left = insert_elem(elem, search_tree->left);
    } else if (elem > search_tree->elem) {
        // 如果指定的元素大于当前节点的元素值，就向该树的右子树移动
        search_tree->right = insert_elem(elem, search_tree->right);
    }
    // 如果目标值已经存在在树中，那什么也不做
    // 返回当前子树
    return search_tree;
}

// 删除二叉查找树中的一个元素
SearchTree delete_elem(ElementType target, SearchTree search_tree) {
    Position tempNode;
    // 处理子树为空的情况
    if (search_tree == NULL) {
        fprintf(stderr, "未查找到指定元素");
    } else if (target < search_tree->elem) {
        // 说明目标节点在左子树
        search_tree->left = delete_elem(target, search_tree->left);
    } else if (target > search_tree->elem) {
        // 说明目标节点在右子树
        search_tree->right = delete_elem(target, search_tree->right);
    } else if (search_tree->left && search_tree->right) {
        // 走到这里说明找到了目标节点，并且它有两个子结点
        // 处理思路是，用它的右子树中最小的元素来代替它
        tempNode = find_min(search_tree->right);
        // 用这个节点的值代替当前节点的值
        search_tree->elem = retrieve(tempNode);
        // 删除原来位置的该节点
        search_tree->right = delete_elem(retrieve(search_tree), search_tree->right);
    }
    else
    {
        // 走到这里也是找到了目标节点，并且它仅仅只有一个子结点
        tempNode = search_tree;
        // 更改指针指向
        if (search_tree->left) {
            search_tree = search_tree->left;
        } else {
            search_tree = search_tree->right;
        }
        // 释放节点空间
        free(tempNode);
    }

    return search_tree;
}

// 取出当前节点的值
ElementType retrieve(Position tree_node) {
    if (tree_node == NULL) {
        fprintf(stderr, "参数传递不合理！\n");
        exit(EXIT_FAILURE);
    }

    return tree_node->elem;
}