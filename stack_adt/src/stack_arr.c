#include "../include/stack_arr.h"
#include <stdlib.h>
#include <stdio.h>

// 使用数组实现栈

// 创建一个空栈
Stack CreateStack(int MaxStackSize) {
    // 判断设置的长度是否符合长度限制
    if (MaxStackSize < MINSTACKSIZE) {
        fprintf(stderr, "您指定的长度太短了！\n");
        exit(EXIT_FAILURE);
    }
    Stack s = (Stack)malloc(sizeof(struct StackRecord));
    if (s == NULL) {
        fprintf(stderr, "栈空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 为数组开辟空间
    s->Array = (ElementType *)malloc(MaxStackSize * sizeof(ElementType));
    if (s->Array == NULL) {
        fprintf(stderr, "数据空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 设置容量
    s->Capacity = MaxStackSize;
    // 设置栈的顶部下标
    EmptyTheStack(s);
    return s;
}

// 判断一个栈是否为空
bool IsEmpty(Stack s) {
    return s->TopOfStack == EmptyToS;
}

// 判断一个栈是否已经满了
bool IsFull(Stack s) {
    return s->TopOfStack == s->Capacity - 1;
}

// 将一个栈清空
void EmptyTheStack(Stack s) {
    s->TopOfStack = EmptyToS;
}

// 将一个元素压入栈中
bool Push(Stack s, ElementType elem) {
    // 判断栈是否已满
    if (IsFull(s)) {
        fprintf(stderr, "该栈已满！\n");
        return false;
    }
    s->Array[++s->TopOfStack] = elem;
    return true;
}

// 返回栈顶部元素
ElementType Top(Stack s) {
    if (IsEmpty(s)) {
        fprintf(stderr, "该栈为空！\n");
        return -1;
    }
    return s->Array[s->TopOfStack];
}

// 弹出一个元素
bool Pop(Stack s) {
    if (IsEmpty(s)) {
        fprintf(stderr, "这个栈为空！\n");
        return false;
    }
    s->TopOfStack--;
    return true;
}

// 弹出一个元素，并且返回这个元素
ElementType TopAndPop(Stack s) {
    if (IsEmpty(s)) {
        fprintf(stderr, "该栈为空！\n");
        exit(EXIT_FAILURE);
    }
    return s->Array[s->TopOfStack--];
}
