//
// Created by tigood on 2024/10/27.
//
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
void btree_split_child(const BTree *tree, BTreeNode *target_node_parent, int i) {
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
void btree_traverse(const BTreeNode *node) {
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

// 打印一个b树（该打印是先打印左子树再打印右子树，做不到层级打印，如果需要层级打印需要用到队列，参考之前的例题实现）
// 前置条件：传入要打印的树，和起始节点和当前层数
void btree_print(BTree *tree, BTreeNode *node, int layer) {
    // 记录当前的节点
    BTreeNode *curr_node = node;
    // 判断树是否为空
    if (curr_node) {
        // 走到这里就说明当前的树不为空
        printf("\n当前是第%d层，一共有%d个关键字，", layer, node->key_count);
        curr_node->is_leaf ? printf("当前是叶子节点\n") : printf("当前不是叶子节点！\n");
        // 打印当前节点的键数
        for (int i = 0; i < node->key_count; i++) {
            printf("%d ", node->keys[i]);
        }
        // 结束当前节点的打印
        printf("\n");
        // 层数叠加
        layer++;
        for (int i = 0; i <= node->key_count; i++) {
            if (curr_node->childrens[i]) {
                btree_print(tree, curr_node->childrens[i], layer);
            }
        }
    }
    else
        printf("该树为空，打印失败！\n");
}

// 二分查找法查找元素
int btree_binary_search(const BTreeNode *target_node, KeyValue k_val) {
    // 参数合法性检测
    if (target_node == NULL) {
        fprintf(stderr, "参数传递不合理！\n");
        return -1;  // 代表未查找到
    }

    // 计算当前节点键的低位和高位
    int low = 0, height = target_node->key_count - 1;
    int mid;  // 中间位置的坐标
    while (low <= height) {
        mid = low + (height - low) / 2;
        if (target_node->keys[mid] == k_val) {
            return mid;
        } else if (target_node->keys[mid] < k_val) {
            low = mid + 1;
        } else {
            height = mid - 1;
        }
    }
    // 走到这里就说明没有找到
    return -1;
}

// 节点的合并
void btree_merge(BTree *tree, BTreeNode **target_node_ref, int index) {
    BTreeNode *target_node = *target_node_ref;
    // 检测参数合法性
    if (tree == NULL || target_node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    BTreeNode *left = target_node->childrens[index];
    BTreeNode *right = target_node->childrens[index + 1];

    // 数据合并
    // 注解：如果执行了该合并函数，说明这个左右这两个的子树都小于或者等于M / 2 - 1，即DRGEE - 1，所以不用担心数组过界
    left->keys[tree->t - 1] = target_node->keys[index];
    // 将右子树中的元素移动到右子树中
    for (int i = 0; i < tree->t - 1; i++) {
        left->keys[tree->t + i] = right->keys[i];
    }
    // 如果左右子节点不是叶子节点的话，那么他们的子树也需要处理
    if (!left->is_leaf) {
        // 走到这里说明该节点是内部节点，现在处理右子树的子树
        for (int i = 0; i < tree->t; i++) {
            left->childrens[tree->t + i] = right->childrens[i];
        }
    }
    // left从父节点拿到了一个1个key，从右子树拿到了t - 1个key，所以一共拿到了k个key
    left->key_count += tree->t;

    // 释放右子节点
    btree_dispose_node(right);

    // 处理target_node节点
    for (int i = index + 1; i < target_node->key_count; i++) {
        target_node->keys[i - 1] = target_node->keys[i];
        target_node->childrens[i] = target_node->childrens[i + 1];
    }
    target_node->childrens[target_node->key_count + 1] = NULL;
    target_node->key_count--;  // key的数量-1,因为下沉了一个

    // target_node节点的键下沉后就没了，让left代替它
    if (target_node->key_count == 0) {
        *target_node_ref = left;
        btree_dispose_node(target_node);
    }
}

// 删除的节点函数的辅助函数
void btree_delete_key_recu(BTree *tree, BTreeNode *node, KeyValue k_val) {
    // 参数合法性检测
    if (tree == NULL || node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    // 找到要删除节点的位置
    while (index < node->key_count && k_val > node->keys[index]) {
        index++;
    }

    // 判断是否找到了，找到了就进行删除的逻辑，没有找到就去它的子树中继续寻找
    if (index < node->key_count && k_val == node->keys[index]) {
        // 走到这里面说明找到了，执行删除逻辑
        // 删除的时候存在一下几种情况
        // 1.叶子节点
        // 2.左边的子节点的key数量大于T - 1
        // 3.右边的子节点的key数量大于T - 1
        // 4.左右都不满足，也不是叶子节点，就要进行合并操作了
        if (node->is_leaf) {
            // 走到这里说明到叶子节点了
            for (int i = 0; i < node->key_count - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }

            // 更新节点信息
            node->keys[node->key_count - 1] = 0;
            node->key_count--;
            if (node->key_count == 0 && tree->root == node) {
                free(node);
                tree->root = NULL;
            }
            return;
        } else if (node->childrens[index]->key_count >= tree->t) {
            // 走到这里说明左子树的key数量够，可以借
            BTreeNode *left = node->childrens[index];
            // 用左子树的最后一个关键字来代替当前节点的关键字
            node->keys[index] = left->keys[left->key_count - 1];

            // 删除原左子树中的该值
            btree_delete_key_recu(tree, left, left->keys[left->key_count - 1]);
        } else if (node->childrens[index + 1]->key_count >= tree->t) {
            // 走到这里说明右子树的key数量够，可以借
            BTreeNode *right = node->childrens[index + 1];
            // 用右子树的第一个关键字来代替当前节点的关键字
            node->keys[index] = right->keys[0];

            // 删除原右子树中的节点
            btree_delete_key_recu(tree, right, right->keys[0]);
        } else {
            // 走到这里说明即不是叶子节点，也不是
            // 合并节点 经过筛选，它肯定不是叶子节点，所以直接将node关键字下沉，然后合并左右子树
            btree_merge(tree, &node, index);
            // 合并之后，再删除指定元素
            btree_delete_key_recu(tree, node->childrens[index], k_val);
        }
    } else {
        // 走到这里说明没有找到，继续寻找子节点
        
    }
}