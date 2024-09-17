#ifndef _STACK
#define _STACK
#include <stdio.h>
#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

// 判断这个栈是否为空
// 前置条件：传入一个初始化完成的栈
// 后值条件：返回一个bool值，true表示为空，否则表示不为空
bool IsEmpty(Stack);

// 创建一个空栈
// 前置条件：null
// 后值条件：返回一个创建好的空栈
Stack CreateStack(void);

// 释放一个栈例程
// 前置条件：传入一个已经初始化的栈
// 后置条件：这个栈内容清空，并且空间被释放
void DisposeStack(Stack);

// 将一个栈清空
// 前置条件：传入一个已经初始化的栈
// 将这个栈的内容清空
void MakeEmpty(Stack);

// 将一个元素压入栈
// 前置条件：传入一个将要压入的元素，和一个指定的初始化完成的栈
// 后置条件：将这个元素压入栈，如果成功返回true，否则返回false
bool Push(Stack, ElementType);

// 返回栈顶的元素
// 前置条件：传入一个指定的初始化完成的栈
// 后值条件：返回一个该栈的顶部元素
ElementType Top(Stack);

// 在栈中弹出一个元素
// 前置条件：传入一个指定的初始化完成的栈
// 后置条件：返回该被弹出的顶部元素
ElementType Pop(Stack);

#endif