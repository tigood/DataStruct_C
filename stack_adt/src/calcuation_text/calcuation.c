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

void eat_line(void) {
    while (getchar() != '\n')
        continue;
}

// 幂运算符的辅助运算
double fast_pow(double base, int exp) {
    // 如果指数为0
    if (exp == 0) {
        return 1.0;
    }

    // 如果指数小于0
    if (exp < 0) {
        base = 1 / base;
        exp = -exp;
    }

    double result = 1.0;
    while (exp > 0)
    {
        // 如果指数为奇数
        if (exp % 2 != 0) {
            result *= base;
        }
        // 基数翻倍
        base *= base;
        // 指数减半，即 5^4 == 25^2
        exp /= 2;
    }

    return result;
}

/*
方法的实现
*/

// 判断字符是否为运算符
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^')
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
        case '^':
            return 3;
        default:
            return 0; // 默认的最低优先级
    }
}

// 中缀表达式变为后缀表达式
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
            // 将这个字符封装为一个字符串
            char *operatorStr = (char *)malloc(2);
            operatorStr[0] = *temp_per;
            operatorStr[1] = '\0';
            // 判断这个栈是否为空，如果为空直接加入
            if (IsEmpty(oper_stack)) {
                // 将该字符加入栈中
                Push(oper_stack, operatorStr);
            } else {
                if (*temp_per == '(') {
                    Push(oper_stack, operatorStr);
                } else if (*temp_per == ')') {
                    // 将栈中的元素弹出，一直到（
                    while (!IsEmpty(oper_stack) && Top(oper_stack)[0] != '(')
                    {
                        // 添加到输出列表中
                        char *oldElem = Pop(oper_stack);
                        *(temp_result++) = oldElem[0];  // 获取字符
                        *(temp_result++) = ' ';
                        free(oldElem);
                    }
                    // 将(弹出
                    free(Pop(oper_stack));
                } else {
                    // 如果这个栈不为空，则判断优先级
                    // 将栈中优先级大于这个运算符的运算符弹出来添加到输出列表中
                    while (!IsEmpty(oper_stack) && isHigher(Top(oper_stack)[0], *temp_per)) {
                        char *oldElem = Pop(oper_stack);
                        *(temp_result++) = oldElem[0];  // 获取字符
                        *(temp_result++) = ' ';
                        free(oldElem);
                    }
                    // 将当前字符加入栈中
                    Push(oper_stack, operatorStr);
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
        char *oldElem = Pop(oper_stack);
        *(temp_result++) = oldElem[0];
        *(temp_result++) = ' ';
        free(oldElem);
    }
    // 释放栈例程
    DisposeStack(oper_stack);
    *temp_result = '\0';
    return result_str;
}

// 根据运算符计算两个整数
double calcuation_two_nums(const char* num1, const char* num2, const char* oper) {
    double inum1 = atoi(num1);
    double inum2 = atoi(num2);
    if (strcmp(oper, "+") == 0)
    {
        return inum1 + inum2;
    }
    else if (strcmp(oper, "-") == 0)
    {
        return inum1 - inum2;
    }
    else if (strcmp(oper, "*") == 0)
    {
        return inum1 * inum2;
    }
    else if (strcmp(oper, "/") == 0)
    {
        return inum1 / inum2;
    }
    else if (strcmp(oper, "^") == 0)
    {
        return fast_pow(inum1, inum2);
    }
    // 默认返回
    return 0.0;
}

// 计算后缀表达式的值
double calcuationBySuffix(const char *formula) {
    // 创建一个栈
    // 遇到操作数，就将操作数压入栈中
    // 遇到运算符，就在栈中弹出两个操作数进行计算
    // 计算完毕之后再将结果压入栈中
    // 循环到算式结束
    Stack operand_stack = CreateStack();
    const char *temp_formula = formula;
    while (*temp_formula != '\0')
    {
        if (*temp_formula == ' ') {
            temp_formula++;
            continue;
        }
        // 将字符封装为一个字符串
        char *formualStr = (char *)malloc(2);
        formualStr[0] = *temp_formula;
        formualStr[1] = '\0';
        // 如果是一个操作数，就将这个操作数压入栈中
        if (!isOperator(*temp_formula)) {
            Push(operand_stack, formualStr);
        } else {
            // 如果是一个操作符就从栈中弹出两个数计算
            char *num1 = Pop(operand_stack);
            char *num2 = Pop(operand_stack);
            double cal_result = calcuation_two_nums(num1, num2, formualStr);
            free(num1);
            free(num2);
            free(formualStr);
            // 将计算的结果转换为字符串，然后重新存入栈中
            char resultStr[20];
            snprintf(resultStr, sizeof(resultStr), "%.2f", cal_result);
            Push(operand_stack, resultStr);
        }
        temp_formula++;
    }
    // 执行完毕之后将最后的结果从栈中取出来
    char *result = Pop(operand_stack);
    double iresult = atoi(result);
    free(result);
    DisposeStack(operand_stack);
    return iresult;
}

// 读取用户输入的算式
char *getUserInput(char *st, int n) {
    printf("请输入您要计算的算式（中缀）:\n");
    char *result_val = s_gets(st, n);
    return result_val;
}

// 计算器系统运行函数
void cal_sys_run(void) {
    printf("欢迎来到计算器系统！\n");
    while (true)
    {
        char userInput[MAXLEN];
        getUserInput(userInput, MAXLEN);
        if (strcmp(userInput, "q") == 0)
        {
            break;
        }
        // 将输入的算式转换并计算
        double result = calcuationBySuffix(infixToSuffix(userInput));
        printf("运算结果为：%.2f\n", result);
        printf("是否继续计算？(y/n)\n");
        char choose_ch = getchar();
        eat_line();
        if (choose_ch == 'n')
            break;
    }
    printf("程序结束！bye\n");
}