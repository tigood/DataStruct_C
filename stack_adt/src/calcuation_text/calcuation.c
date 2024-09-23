#include "calcuation.h"
#include "ch_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
辅助函数
*/

// 封装字符串的读取
char* s_gets(char* st, int n) {
    char *result_val;
    result_val = fgets(st, n, stdin);
    if (result_val) {
        int i = 0;
        while (result_val[i] != '\n' && result_val[i] != '\0')
            i++;
        // 走到这里说明找到了
        if (result_val[i] == '\n')
            result_val[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return result_val;
}

/*
方法的实现
*/

// 判断字符是否为运算符
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
        return true;
    return false;
}

// 判断两个运算符的优先级高低
bool isHigher(char ch1, char ch2) {
    if (ch1 == '(' || ch1 == ')') return false;  // 括号不参与优先级比较
    int precedence1 = getPrecedence(ch1);
    int precedence2 = getPrecedence(ch2);

    return precedence1 >= precedence2;
}

// 获取运算符优先级
int getPrecedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // 默认的最低优先级
    }
}

char *infixToSuffix(const char *per){
    // 创建一个栈用来存储运算符
    Stack oper_stack = CreateStack();

    // 创建一个输出字符串来存储后缀结果
    char *result_str = (char *)malloc(sizeof(char) * strlen(per) * 2);

    if (result_str == NULL) {
        fprintf(stderr, "空间分配失败！\n");
        exit(EXIT_FAILURE);
    }

    // 遍历前缀算式，进行转换
    const char *temp_per = per;
    char *temp_result = result_str;
    while (*temp_per != '\0')
    {

        if (*temp_per == ' ')
        {
            temp_per++;
            continue;
        }
        if(isOperator(*temp_per)) {
            // 如果当前字符是一个运算符
            // 判断这个栈是否为空，如果为空直接加入
            if (IsEmpty(oper_stack)) {
                // 将该字符加入栈中
                Push(oper_stack, *temp_per);
            } else {
                if (*temp_per == '(') {
                    Push(oper_stack, *temp_per);
                } else if (*temp_per == ')') {
                    // 将栈中的元素弹出，一直到（
                    while (!IsEmpty(oper_stack) && Top(oper_stack) != '(')
                    {
                        // 添加到输出列表中
                        *(temp_result++) = Pop(oper_stack);
                        *(temp_result++) = ' ';
                    }
                    // 将(弹出
                    Pop(oper_stack);
                } else {
                    // 如果这个栈不为空，则判断优先级
                    // 将栈中优先级大于这个运算符的运算符弹出来添加到输出列表中
                    while (!IsEmpty(oper_stack) && isHigher(Top(oper_stack), *temp_per)) {
                        *(temp_result++) = Pop(oper_stack);
                        *(temp_result++) = ' ';
                    }
                    // 将当前字符加入栈中
                    Push(oper_stack, *temp_per);
                }
            }
        } else {
            // 当前字符为一个数，将他添加到输出列表中
            *(temp_result++) = *temp_per;
            *(temp_result++) = ' ';
        }
        temp_per++;
    }
    // 如果栈中还有剩余运算符则逐一弹出
    while (!IsEmpty(oper_stack))
    {
        *(temp_result++) = Pop(oper_stack);
        *(temp_result++) = ' ';
    }
    // 释放栈例程
    DisposeStack(oper_stack);
    *temp_result = '\0';
    return result_str;
}

