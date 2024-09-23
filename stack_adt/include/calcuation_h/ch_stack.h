/*
这是栈的链表实现，除了创建一个空栈其他的操作都是常数级别的复杂度，
缺点：不过有一个缺点，就是我们在压入元素和弹出元素操作时，都会用到mallo 和 free来开辟和释放空间
    这两个操作是比较耗费时间的
解决方案：我们可以在一开始的时候创建第2个栈，在我们第一个栈弹出元素时，不直接释放这个元素，而是存入第二个栈
    在压入一个元素时我们也不直接开辟空间，而是先检查第二个栈中有没有，如果有就直接拿来用
*/
#ifndef _CH_STACK
#define _CH_STACK
#include <stdio.h>
#include <stdbool.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef char* ElementType;

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