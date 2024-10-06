/*
后缀表达式转为中缀表达式
思路：
    1. 实例化一个栈
    2. 遍历后缀表达式
        1. 遇到操作数就将其压入栈中
        2. 遇到操作符就从栈中取出两个操作值，将这个三个拼接为一个中缀操作式，将这个式子压入栈中
    3. 将最后的结果式子从栈中弹出
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct Stack {
    char* items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char* item) {
    if (!isFull(s)) {
        s->items[++s->top] = item;
    }
}

char* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return NULL;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

char* postfixToInfix(const char* postfix) {
    Stack s;
    initStack(&s);
    char* result = (char*)malloc(MAX * sizeof(char));
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(&s, operand);
        } else if (isOperator(postfix[i])) {
            char* right = pop(&s);
            char* left = pop(&s);
            char* expr = (char*)malloc(MAX * sizeof(char));
            sprintf(expr, "(%s %c %s)", left, postfix[i], right);
            push(&s, expr);
            free(left);
            free(right);
        }
    }
    
    return pop(&s);
}

int main() {
    const char* postfix = "ab+cde+**"; // 示例后缀表达式
    char* infix = postfixToInfix(postfix);
    printf("中缀表达式: %s\n", infix);
    free(infix);
    return 0;
}
