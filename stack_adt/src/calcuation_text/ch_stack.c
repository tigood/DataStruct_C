#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ch_stack.h"

// 节点的实现
struct Node{
    ElementType elem;
    PtrToNode next;
};

// 栈的实现

// 判断一个栈是否为空
bool IsEmpty(Stack s) {
    return s->next == NULL;
}

// 创建一个空栈
Stack CreateStack(void) {
    Stack s = (Stack)malloc(sizeof(struct Node));
    // 判断是否分配成功
    if (s == NULL) {
        fprintf(stderr, "空间分配失败！\n");
        exit(EXIT_FAILURE);
    }
    // 将新栈的数据初始化
    s->next = NULL;
    MakeEmpty(s);
    return s;
}

// 将栈清空
void MakeEmpty(Stack s) {
    if (s == NULL)
    {
        fprintf(stderr, "请传入一个初始化完成的栈！\n");
        exit(EXIT_FAILURE);
    }
    while (!IsEmpty(s))
        Pop(s);
}

// 将一个元素压入一个栈
bool Push(Stack s, ElementType newElem) {
    // 创建一个新的节点
    PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
    // 判断是否创建失败
    if (newNode == NULL) {
        fprintf(stderr, "空间分配失败！\n");
        return false;
    }
    // 分配成功之后初始化这个节点
    newNode->elem = strdup(newElem);
    newNode->next = s->next;
    s->next = newNode;
    return true;
}

// 返回栈顶元素
ElementType Top(Stack s) {
    if (IsEmpty(s)) {
        fprintf(stderr, "该栈为空栈！\n");
        exit(EXIT_FAILURE);
    }
    return s->next->elem;
}

// 弹出栈顶元素
ElementType Pop(Stack s) {
    if (IsEmpty(s)) {
        fprintf(stderr, "该栈为空!\n");
        exit(EXIT_FAILURE);
    }
    // 存储要删除的值
    ElementType oldVal = s->next->elem;
    // 存储指向这个将要删除空间的指针
    PtrToNode ptrToOldVal = s->next;
    // 将该节点从栈中删除
    s->next = s->next->next;
    // 释放该删除空间
    free(ptrToOldVal);
    // 返回被删除的值
    return oldVal;
}

// 释放一个栈例程
void DisposeStack(Stack s) {
    MakeEmpty(s);
    free(s);
}
