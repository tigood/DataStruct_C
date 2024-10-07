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

// 检测栈1顶部元素
ElementType top_1(TwoStacks *two_stacks) {
    // 判断栈是否为空
    if (is_empty_1(two_stacks)) {
        fprintf(stderr, "栈为空，访问栈顶失败！\n");
        exit(EXIT_FAILURE);
    }
    
    // 返回栈顶
    return two_stacks->arr[two_stacks->top1];
}

// 检测栈2顶部元素
ElementType top_2(TwoStacks *two_stacks) {
    // 判断栈是否为空
    if (is_empty_2(two_stacks)) {
        fprintf(stderr, "栈为空，访问栈顶失败！\n");
        exit(EXIT_FAILURE);
    }

    // 返回栈顶
    return two_stacks->arr[two_stacks->top2];
}

// 完成3.22题的附加操作
/*
3.22题的实现思路：
    通过一个双栈实现功能，实际的所有元素存储都先压入栈1中，即栈1保存了实际的元素内容
    而栈2用来记录一系列的最小值，返回最小值的时候直接返回栈2的顶部就可以了
    添加的时候先将元素压入栈1,如果这个元素比栈1的栈顶元素小或者相等，则将这个元素也压入栈2
    弹出元素实际上就是弹出栈1的元素，如果这个弹出的元素
*/

// 附加功能：找到栈中的最小元素，即返回栈二的顶部元素
ElementType find_min(TwoStacks *two_stacks) {
    return top_2(two_stacks);
}

// 在栈中添加元素
void push(ElementType elem, TwoStacks *two_stacks) {
    // 无论如何都会插入栈1
    push_1(elem, two_stacks);

    // 如果栈2为空直接插入或者elem小于等于栈2顶部
    if (is_empty_2(two_stacks) || elem <= top_2(two_stacks)) {
        push_2(elem, two_stacks);
    }
}

// 在栈中弹出元素
ElementType pop(TwoStacks *two_stacks) {
    // 首先弹出实际栈中元素
    ElementType result = pop_1(two_stacks);
    if (result == top_2(two_stacks))
    {
        // 如果栈1弹出元素与栈2栈顶相同，栈2也弹出元素，清除这个最小值记录
        pop_2(two_stacks);
    }

    return result;
}

// 返回栈顶元素
ElementType top(TwoStacks *two_stacks) {
    return top_1(two_stacks);
}