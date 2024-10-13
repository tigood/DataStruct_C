#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "avl_tree.h"

struct AvlNode {
    ElementType elem;
    AvlTree left;
    AvlTree right;
    int height;
};

// 计算节点的高度 static函数，只能在当前源文件中使用
static int height(Position p) {
    if (p == NULL) {
        return -1;
    } else {
        return p->height;
    }
}

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

// 左子树过高要执行的单旋转 即左-左单旋转
/*仅当k2有左子树的时候才可以调用这个函数*/
/*在k2和它的左节点之间执行一次旋转*/
/*重新更新高度，并且返回一个新的节点*/
static Position single_rotate_with_left(Position k2) {
    // 定义k1
    Position k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    // 更新高度
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k2)) + 1;

    // 返回新的节点
    return k1;
}

// 右子树过高的时候要执行的单旋转 即右-右单旋转
/*仅当k2有右子树的时候才可以调用这个函数*/
/*在k2和它的右节点之间执行一次旋转*/
/*重新更新高度，并且返回一个新的节点*/
static Position signle_rotate_whit_right(Position k2) {
    Position k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    // 更新高度
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), height(k2)) + 1;

    return k1;
}

// 该节点失衡是因为在左子树的右子树中插入节点导致的 即左-右双旋转
/*仅当k3有一个左子树k1，并且k3的左子树又有一个右子树k2的时候才可以调用这个函数*/
/*更新高度并且返回一个新的节点*/
static Position double_rotate_with_left(Position k3) {
    // 首先k1和k2先执行 右-右单旋转
    k3->left = signle_rotate_whit_right(k3->left);

    // 在对k3和k2执行左-左单旋转
    return single_rotate_with_left(k3);
}

// 该节点失衡是因为在右子树的左子树中插入节点导致的 即 右-左双旋转
/*仅当k3有一个右子树k1，并且k1有一个左子树k2的时候才可以调用该函数*/
/*更新高度，并且返回一个新的节点*/
static Position double_rotate_with_right(Position k3) {
    // 首先k1和k2执行左-左单旋转
    k3->right = single_rotate_with_left(k3->right);

    // 然后对k3和k2执行右-右单旋转
    return signle_rotate_whit_right(k3);
}

// 将avl树置空
AvlTree make_empty(AvlTree avl_tree) {
    // 后序遍历
    if (avl_tree != NULL) {
        make_empty(avl_tree->left);
        make_empty(avl_tree->right);
        free(avl_tree);
    }

    return NULL;
}

// 查找目标节点
Position find(ElementType target, AvlTree avl_tree) {
    if (avl_tree == NULL) {
        printf("未找到指定元素:%d\n", target);
        return NULL;
    }
    else if (target < retrieve(avl_tree))
    {
        // 目标节点小于当前节点的值，那就去左子树中继续找
        return find(target, avl_tree->left);
    }
    else if (target > retrieve(avl_tree))
    {
        // 目标节点大于当前节点的值，那就去右子树中继续找
        return find(target, avl_tree->right);
    }
    else
    {
        // 走到这里就说明是找到了
        return avl_tree;
    }
}

// 查找最小值
Position find_min(AvlTree avl_tree) {
    // 非空检测
    if (avl_tree == NULL)
        return NULL;
    
    if (avl_tree->left == NULL) {
        // 走到这里说明这里就是最小的节点
        return avl_tree;
    } else {
        // 走到这里说明还未找到最小的节点
        return find_min(avl_tree->left);
    }
}

// 查找最大值
Position find_max(AvlTree avl_tree) {
    // 非空检测
    if (avl_tree == NULL)
        return NULL;

    if (avl_tree->right == NULL) {
        // 走到这里说明，当前节点就是最大的
        return avl_tree;
    } else {
        // 否则就是还没找到最大的节点，继续递归
        return find_max(avl_tree->right);
    }
}

// 插入一个元素
AvlTree insert_elem(ElementType elem, AvlTree avl_tree) {
    // 如果avl_tree树为空，则创建新节点
    if (avl_tree == NULL) {
        avl_tree = (AvlTree)malloc(sizeof(struct AvlNode));\
        
        // 判断节点是否正常开辟
        if (avl_tree == NULL) {
            fprintf(stderr, "空间开辟失败！\n");
            exit(EXIT_FAILURE);
        }

        // 为节点初始化
        avl_tree->elem = elem;
        avl_tree->height = 0;
        avl_tree->left = avl_tree->right = NULL;
    } else if (elem < retrieve(avl_tree)) {
        // 递归的寻找该插入的位置
        avl_tree->left = insert_elem(elem, avl_tree->left);
        
        // 插入之后检查一下是否平衡
        if (height(avl_tree->left) - height(avl_tree->right) == 2) {
            // 如果走到这里就说明超出了限制，已经不平衡了
            // 我们要根据节点插入的位置来决定执行怎样的旋转
            if (elem < retrieve(avl_tree->left)) {
                // 走到这里说明，目标元素比左子节点还要小，就要插到左子树的左子树，所以这里左-左单旋转就可以解决
                avl_tree = single_rotate_with_left(avl_tree);
            } else {
                // 走到这里，就是要插入到左子树的右子树中，就要执行左-右双旋转
                avl_tree = double_rotate_with_left(avl_tree);
            }
        }
    } else if (elem > retrieve(avl_tree)) {
        // 走到这里就说明，要将该节点插入到右子树中
        // 递归寻找合理的插入位置
        avl_tree->right = insert_elem(elem, avl_tree->right);

        // 插入完成后检测当前节点是否平衡
        if (height(avl_tree->right) - height(avl_tree->left) == 2) {
            // 如果走到这里就说明不平衡了
            // 根据插入的位置来决定如何旋转
            if (elem > retrieve(avl_tree->right)) {
                // 如果大于右子节点，则插入到右子节点的右子树中，即右-右单旋转
                avl_tree = signle_rotate_whit_right(avl_tree);
            } else {
                // 则右-左双旋转
                avl_tree = double_rotate_with_right(avl_tree);
            }
        }
    }

    // 更新当前节点的高度
    avl_tree->height = max(height(avl_tree->left), height(avl_tree->right)) + 1;
    return avl_tree;
}

// 获取节点的值
ElementType retrieve(Position node) {
    if (node == NULL) {
        fprintf(stderr, "参数传递不合理！\n");
        exit(EXIT_FAILURE);
    }

    return node->elem;
}