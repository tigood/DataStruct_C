/*
通过一个数组实现两个栈例程
思路：
    一个栈同数组的头部开始为往后增长
    另一个栈从数组的尾部开始往前增长
*/
#ifndef _TWO_STACKS_BY_ONE_ARR
#define _TWO_STACKS_BY_ONE_ARR
#include <stdbool.h>
#define MAX 100

typedef int ElementType;
typedef struct {
    ElementType arr[MAX];
    int top1;
    int top2;
} TwoStacks;

// 初始化一个双栈
void init_stacks(TwoStacks *);

// 判断该数组是否已经用满了
bool is_full(TwoStacks *);

// 判断第一个栈是否为空
bool is_empty_1(TwoStacks *);

// 判断第二个栈是否为空
bool is_empty_2(TwoStacks *);

// 在第一个栈顶压入元素
void push_1(ElementType, TwoStacks *);

// 在第二个栈顶压入元素
void push_2(ElementType, TwoStacks *);

// 在第一个栈顶弹出元素
ElementType pop_1(TwoStacks *);

// 在第二个栈顶弹出元素
ElementType pop_2(TwoStacks *);
#endif