#include "../include/stack.h"

void stack_text() {
    // 创建一个空栈
    printf("创建一个空栈！\n");
    Stack s = CreateStack();
    // 测试IsEmpty函数
    if (IsEmpty(s)) {
        printf("当前栈为空！\n");
    } else {
        printf("当前栈不为空！\n");
    }
    printf("依次压入两个元素，2和3\n");
    // 测试Push函数
    Push(s, 2);
    Push(s, 3);
    // 再次测试当前栈是否为空
    if (IsEmpty(s)) {
        printf("当前栈为空！\n");
    } else {
        printf("当前栈不为空！\n");
    }
    // 测试Top函数
    printf("当前栈顶元素为：%d\n", Top(s));
    // 测试Pop函数
    while (!IsEmpty(s)) {
        printf("弹出元素：%d\n", Pop(s));
    }
    // 最后测试是否为空
    if (IsEmpty(s)) {
        printf("栈已经为空！\n");
    } else {
        printf("栈不为空！\n");
    }
}

int main() {
    stack_text();

    return 0;
}