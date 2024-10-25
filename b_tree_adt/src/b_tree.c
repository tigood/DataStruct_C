#include "../include/b_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 创建一个节点 
// 前置条件：传入该节点所在树的度->DEGREE is_leaf表示是否是子节点
// 后置条件：创建一个节点并返回
BTreeNode *btree_create_node(int t, bool is_leaf) {
    // 创建节点
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    // 判断空间是否开辟成功
    if (!node) {
        fprintf(stderr, "节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 对属性进行初始化
    node->is_leaf = is_leaf;
    node->keys = (KeyValue *)calloc(2 * t - 1, sizeof(KeyValue));
    node->childrens = (BTreeNode **)calloc(2 * t, sizeof(BTreeNode *));
    node->key_count = 0; // 当前不存在key

    return node;
}

// 节点的销毁
// 前置条件：传入指向节点的指针
// 后置条件：该节点内存被销毁
void btree_dispose_node(BTreeNode *node) {
    // 检测参数合法性
    if (node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    free(node->childrens);
    free(node->keys);
    free(node);
}

// 创建一颗b树
// 前置条件：传入一个指向b树的指针
// 后置条件：创建一个根节点
void btree_create(BTree *tree, int t) {
    if (tree == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    tree->t = t;
    tree->root = btree_create_node(t, true);
}

/*
分裂节点：
分裂节点是用于插入节点的，由于插入节点是自上而下的，因此如果找到某个节点已经满了的话，就需要分裂
如果分裂到了该节点，那么说明它的父节点都不是满的
*/
void btree_split_child(BTree *tree, BTreeNode *target_node_parent, int i) {
    // 检测参数合法性
    if (tree == NULL || target_node_parent == NULL) {
        fprintf(stderr, "参数传递不合法！\n");
        exit(EXIT_FAILURE);
    }

    int t = tree->t;  // 记录当前树的度数

    // 找到要分裂的节点
    BTreeNode *target_node = target_node_parent->childrens[i];
    // 创建一个新的节点，存储分裂之后的后半部分元素
    BTreeNode *new_node = btree_create_node(t, target_node->is_leaf);

    new_node->key_count = t - 1;  // 设置该新节点的键数
    for (int j = 0; j < t - 1; j++) {
        new_node->keys[j] = target_node->keys[j + t];
    }
    // 如果不是叶子节点，那么还需要将该节点的子节点们也都放到新的节点中
    if (!target_node->is_leaf) {
        for (int j = 0; j < t; j++) {
            new_node->childrens[j] = target_node->childrens[j + t];
        }
    }

    // 更新分裂完成后当前节点的键数量
    target_node->key_count = t - 1;

    // 父节点的子节点数组后面的键往后移，留出新节点空间
    // 这里移动的children数组，但是用的是key_count的原因是，key_count的数量肯定是children的数量的-1
    for (int j = target_node_parent->key_count; j >= i + 1; j--) {
        target_node_parent->childrens[j + 1] = target_node_parent->childrens[j];
    }
    target_node_parent->childrens[i + 1] = new_node;  // 插入新节点

    // key数组向后移，为新的key留出空间
    for (int j = target_node_parent->key_count - 1; j >= i; j--) {
        target_node_parent->keys[j + 1] = target_node_parent->keys[j];
    }
    target_node_parent->keys[i] = target_node->keys[t - 1];  // 将分裂节点的中间节点插入父节点的keys数组中
    target_node_parent->key_count++;  // key的数量增加
}

/*
树根节点没有满的时候插入  （辅助函数）
*/
void btree_insert_nofull(BTree *tree, BTreeNode *target_node, KeyValue k_val) {
    int index = target_node->key_count - 1;   // 该index为keys数组最后一个元素的下标

    // 判断要插入的节点是叶子节点还是内部节点
    if (target_node->is_leaf) {
        // 走到这里就说明是叶子节点
        // 找到要插入的位置
        while (index >= 0 && target_node->keys[index] > k_val) {
            // 由于这里是未满节点的插入操作，所以不用害怕index + 1会出界
            target_node->keys[index + 1] = target_node->keys[index];
            index--;
        }
        // 在找到的位置中插入
        target_node->keys[index + 1] = k_val;
        target_node->key_count++;  // 该节点的键数量增加
        printf("插入了节点：%d\n", k_val);
    }
    else
    {
        // 走到这里就说明是内部节点
        // 找到该插入到那个子节点中
        while (index >= 0 && target_node->keys[index] > k_val)
            index--;
        // 第一个小于k_val的关键字是index，那么该节点就应该插入到index + 1这个子节点中
        // 判断该没目标节点是否满了
        if (target_node->childrens[index + 1]->key_count == 2 * (tree->t) - 1) {
            // 走到这里就说明满了，需要分裂该节点
            btree_split_child(tree, target_node, index + 1);
            // 判断key是要插入分裂后的前半部分节点还是后半部分节点
            if (k_val > target_node->keys[index + 1])
                index++;
        }
        // 插入节点
        btree_insert_nofull(tree, target_node->childrens[index + 1], k_val);
    }
}

/*
节点的插入
*/
void btree_insert(BTree *tree, KeyValue k_val) {
    // 获取该树的根节点
    BTreeNode *root = tree->root;
    // 判断该根节点是否已满
    if (root->key_count == 2 * tree->t - 1) {
        // 走到这里说明满了，进行根节点分裂
        // 创建新的节点作为根节点
        BTreeNode *new_root = btree_create_node(tree->t, false);
        tree->root = new_root;
        new_root->childrens[0] = root;  // 将旧的根节点作为新根节点的
        // 分裂该节点
        btree_split_child(tree, new_root, 0);

        // 判断该节点是要插入分裂之后的0号子树还是1号子树
        int index = 0;
        if (new_root->keys[0] < k_val)
            index++;
        btree_insert_nofull(tree, new_root->childrens[index], k_val);
    } else {
        // 走到这里就说明 根还没有满
        btree_insert_nofull(tree, root, k_val);
    }
}

/*
中序遍历该子树
*/
void btree_traverse(BTreeNode *node) {
    int i = 0;
    for (i = 0; i < node->key_count; i++) {
        if (!node->is_leaf) {
            btree_traverse(node->childrens[i]);
        }
        printf("%d ", node->keys[i]);
    }
    if (!node->is_leaf)
        btree_traverse(node->childrens[i]);
}