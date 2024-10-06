#include "two_stacks_by_one_arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 初始化双栈
void init_stacks(TwoStacks *two_stacks) {
    two_stacks->top1 = -1;
    two_stacks->top2 = MAX;
}

// 判断数组是否已满
bool is_full(TwoStacks *two_stacks) {
    return two_stacks->top1 + 1 == two_stacks->top2;
}

// 判断栈1是否为空
bool is_empty_1(TwoStacks *two_stacks) {
    return two_stacks->top1 == -1;
}

// 判断栈2是否为空
bool is_empty_2(TwoStacks *two_stacks) {
    return two_stacks->top2 == MAX;
}

// 将一个元素压入栈1
void push_1(ElementType elem, TwoStacks *two_stacks) {
    // 检查栈是否已满
    if (is_full(two_stacks)) {
        fprintf(stderr, "栈已满，压入失败！\n");
        exit(EXIT_FAILURE);
    }

    // 将元素压入
    two_stacks->arr[++two_stacks->top1] = elem;
}

// 将一个元素压入栈2
void push_2(ElementType elem, TwoStacks *two_stacks) {
    // 检查栈是否已满
    if (is_full(two_stacks)) {
        fprintf(stderr, "栈已满，压入失败！\n");
        exit(EXIT_FAILURE);
    }

    // 将元素压入
    two_stacks->arr[--two_stacks->top2] = elem;
}

// 在第一个栈顶弹出元素
ElementType pop_1(TwoStacks *two_stacks) {
    if (is_empty_1(two_stacks)) {
        fprintf(stderr, "栈1为空，弹出失败！\n");
        exit(EXIT_FAILURE);
    }

    // 弹出元素
    return two_stacks->arr[two_stacks->top1--];
}

// 在第二个栈顶弹出元素
ElementType pop_2(TwoStacks *two_stacks) {
    if (is_empty_2(two_stacks)) {
        fprintf(stderr, "栈2为空，弹出失败！\n");
        exit(EXIT_FAILURE);
    }

    // 弹出元素
    return two_stacks->arr[two_stacks->top2++];
}