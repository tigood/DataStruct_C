#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

// 实现一个简易的栈
typedef struct {
    char items[MAX];  // 数组
    int top;  // 栈顶下标
} Stack;

// 初始化一个栈
void init_stack(Stack *s) {
    s->top = -1;
}

// 判断栈是否已经满了
bool is_full(Stack *s) {
    return s->top == MAX - 1;
}

// 判断栈是否为空
bool is_empty(Stack *s) {
    return s->top == -1;
}

// 将一个元素压入栈中
void push(Stack *s, char ch) {
    if (!is_full(s)) {
        // 如果栈没有满
        s->items[++s->top] = ch;
    }
}

// 将一个元素从栈中弹出
char pop(Stack *s) {
    // 如果栈为空就报错，退出程序
    if (is_empty(s)) {
        fprintf(stderr, "栈为不空，不能进行弹出操作！\n");
        exit(EXIT_FAILURE);
    }

    // 返回栈顶元素
    return s->items[s->top--];
}

// 检测表达式是否平衡
bool is_banlanced(const char *expr) {
    // 初始化一个栈
    Stack s;
    init_stack(&s);

    // 遍历表达时的字符串
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{' || (expr[i] == '/' && expr[i + 1] == '*')) {
            // 判断是否时/*特殊符号
            if (expr[i] == '/')
                i++;  // 跳过
            push(&s, expr[i]);
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}' || (expr[i] == '*' && expr[i + 1] == '/')) {
            if (expr[i] == '*')
                i++;
            char top = pop(&s);
            if ((expr[i] == ')' && top != '(') || (expr[i] == ']' && top != '[') || (expr[i] == '}' && top != '{') || (expr[i] == '/' && top != '/')) {
                // 走到这里说明不平衡
                printf("'%c' 符号匹配错误，它是第%d个字符!\n", expr[i - 1], i);
                return false;
            }
        }
    }

    // 判断栈是否都被弹出了，否则就是不平衡
    if (!is_empty(&s)) {
        // 走到这里说明有残留
        printf("剩余这些符号没有闭合：");
        char temp;
        while (!is_empty(&s))
        {
            temp = pop(&s);
            printf(" '%c' ", temp);
        }
        printf("\n");
        return false;
    }

    return true;
}

int main(void) {
    char *str_1 = "(hello world[]{)";
    char *str_2 = "(1 + 2 + 3) * (2 * 1)";
    char *str_3 = "(1 + 2) + ([1 + 2";
    if (is_banlanced(str_3))
    {
        printf("该表达式是正确的！\n");
    }
    else
    {
        printf("该表达是不是正确的！\n");
    }

    return 0;
}