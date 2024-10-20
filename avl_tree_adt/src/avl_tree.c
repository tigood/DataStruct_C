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

// 插入元素的非递归实现
AvlTree insert_elem_nr(ElementType elem, AvlTree avl_tree) {
    // 定义一个栈来追踪插入路径
    AvlTree stack[100];
    int top = -1;
    Position parent = NULL;
    Position current = avl_tree;

    // 创建一个新节点
    AvlTree new_node = (AvlTree)malloc(sizeof(struct AvlNode));
    if (new_node == NULL) {
        // 说明空间开辟失败
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化节点
    new_node->elem = elem;
    new_node->left = new_node->right = NULL;
    new_node->height = 0;

    // 寻找插入点
    while (current != NULL) {
        stack[++top] = current;
        parent = current;
        if (elem < retrieve(current)) {
            current = current->left;
        } else if (elem > retrieve(current)) {
            current = current->right;
        } else {
            // 如果已经存在相同的值了，则不插入
            return avl_tree;
        }
    }

    // 插入新节点
    if (parent == NULL) {
        avl_tree = new_node;
    } else if (elem < retrieve(parent)) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    // 自下而上调整树的平衡性
    while (top >= 0) {
        // 回溯节点
        current = stack[top--];

        // 更新当前节点的高度
        current->height = max(height(current->left), height(current->right)) + 1;

        // 检查当前节点是否平衡
        if (height(current->left) - height(current->right) == 2) {
            // 走到这里说明，节点不平衡，且是在左子树插入之后不平衡的
            if (elem < retrieve(current->left)) {
                // 走到这里，说明是左-左单旋转
                current = single_rotate_with_left(current);
            } else {
                // 左-右双旋转
                current = double_rotate_with_left(current);
            }
        } else if (height(current->right) - height(current->left) == 2) {
            // 走到这里说明，节点不平衡，且是在右子树插入之后不平衡的
            if (elem > retrieve(current->right)) {
                // 右-右单旋转
                current = signle_rotate_whit_right(current);
            } else {
                // 右-左单旋转
                current = double_rotate_with_right(current);
            }
        }
    }

    // 将旋转之后的节点，与父节点重新连接
    if (top >= 0) {
        if (current->elem < retrieve(stack[top])) {
            stack[top]->left = current;
        } else {
            stack[top]->right = current;
        }
    } else {
        // 走到这里就说明，父节点是根节点了
        avl_tree = current;
    }

    return avl_tree;
}

// 删除一个元素的非递归实现
AvlTree delete_elem_nr(ElementType target, AvlTree avl_tree) {
    if (avl_tree == NULL) {
        // 提示用户未查找到指定亚unsu
        fprintf(stderr, "未查找到指定元素！\n");
        exit(EXIT_FAILURE);
    }

    // 定义一个栈追踪路径
    AvlTree stack[100];
    int top = -1;
    Position parent = NULL;
    Position current = avl_tree;
    Position target_position = NULL;

    // 查找到要删除的节点
    while (current != NULL) {
        stack[++top] = current;
        if (target < retrieve(current)) {
            parent = current;
            current = current->left;
        } else if (target > retrieve(current)) {
            parent = current;
            current = current->right;
        } else {
            // 找到了待删除的节点
            target_position = current;
            // 退出循环
            break;
        }
    }

    // 如果没有找到目标节点
    if (target_position == NULL) {
        printf("未找到指定要删除的元素！\n");
        return avl_tree;
    }

    // 删除节点，并调整树结构
    if (target_position->left && target_position->right) {
        // 走到这里说明，有两个子节点
        // 找到右子树中的最小节点替换
        AvlTree successor = current->right, successor_parent = current;
        while (successor->left != NULL) {
            stack[++top] = successor;
            successor_parent = successor;
            successor = successor->left;
        }

        // 替换值
        current->elem = successor->elem;
        // 删除最小的节点
        if (successor_parent->left = successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }

        free(successor);
    }
    else
    {
        // 走到这里说明只有一个节点
        AvlTree new_child = current->left ? current->left : current->right;
        if (parent == NULL){
            // 没有父元素
            avl_tree = new_child;
        } else if (parent->left == current) {
            parent->left = new_child;
        } else {
            parent->right = new_child;
        }

        // 释放节点
        free(current);
    }

    // 自下而上调整树的平衡性
    while (top >= 0) {
        // 回溯节点
        current = stack[top--];

        // 更新当前节点的高度
        current->height = max(height(current->left), height(current->right)) + 1;

        // 检查当前节点是否平衡
        if (height(current->left) - height(current->right) == 2) {
            // 走到这里说明，节点不平衡，且是在左子树插入之后不平衡的
            if (target < retrieve(current->left)) {
                // 走到这里，说明是左-左单旋转
                current = single_rotate_with_left(current);
            } else {
                // 左-右双旋转
                current = double_rotate_with_left(current);
            }
        } else if (height(current->right) - height(current->left) == 2) {
            // 走到这里说明，节点不平衡，且是在右子树插入之后不平衡的
            if (target > retrieve(current->right)) {
                // 右-右单旋转
                current = signle_rotate_whit_right(current);
            } else {
                // 右-左单旋转
                current = double_rotate_with_right(current);
            }
        }
    }

    // 将旋转之后的节点，与父节点重新连接
    if (top >= 0) {
        if (current->elem < retrieve(stack[top])) {
            stack[top]->left = current;
        } else {
            stack[top]->right = current;
        }
    } else {
        // 走到这里就说明，父节点是根节点了
        avl_tree = current;
    }

    return avl_tree;
}