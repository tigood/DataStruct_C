/*
栈的数组实现
*/
#ifndef _STACK_ARR
#define _STACK_ARR
#define MINSTACKSIZE (5)
#define EmptyToS (-1)
#include <stdbool.h>

typedef int ElementType;
struct StackRecord;
typedef struct StackRecord *Stack;

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

// 创建一个栈
// 前置条件：要创建俄栈的大小
// 后置条件：返回一个创建好的空栈
Stack CreateStack(int MaxStackSize);

// 释放一个栈实例
// 前置条件：传入一个栈实例
// 后置条件：这个栈实例被释放
void DisposeStack(Stack);

// 判断一个栈是否为空
// 前置条件：传入一个栈
// 后置条件：如果栈为空返回true，否则返回false
bool IsEmpty(Stack);

// 判断一个栈是否已经满了
// 前置条件：传入一个指定栈
// 后置条件：如果栈已经满了，就返回true，否则返回false
bool IsFull(Stack);

// 将一个栈的内容清空
// 前置条件：传入一个栈
// 后置条件：将该栈的内容清空
void EmptyTheStack(Stack);

// 将一个元素压入栈
// 前置条件：传入一个目标栈和一个指定元素
// 后置条件：将这个指定元素压入这个栈
bool Push(Stack, ElementType);

// 返回栈顶元素
// 前置条件：传入一个指定的栈
// 后置条件：返回这个栈的顶部元素
ElementType Top(Stack);

// 弹出一个栈中的元素
// 前置条件：传入一个指定的栈
// 后置条件：弹出这个栈的栈顶元素
bool Pop(Stack);

// 返回栈顶元素然后将这个元素弹出
// 前置条件：传入一个指定栈
// 后置条件：返回栈顶元素，并将这个元素弹出
ElementType TopAndPop(Stack);

#endif