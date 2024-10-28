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

char *infixToSuffix(const char *per){
    Stack oper_stack = CreateStack();
    char *result_str = (char *)malloc(sizeof(char) * strlen(per) * 2);
    if (result_str == NULL) {
        fprintf(stderr, "空间分配失败！\n");
        exit(EXIT_FAILURE);
    }

    const char *temp_per = per;
    char *temp_result = result_str;
    char num_buffer[20];  // 缓存数字
    int buffer_index = 0;

    while (*temp_per != '\0') {
        if (*temp_per == ' ') {
            if (buffer_index > 0) {
                // 遇到空格，说明一个完整数字结束
                num_buffer[buffer_index] = '\0';
                strcpy(temp_result, num_buffer);
                temp_result += buffer_index;
                *(temp_result++) = ' ';
                buffer_index = 0;
            }
            temp_per++;
            continue;
        }

        if (isdigit(*temp_per)) {
            // 累积数字到缓冲区
            num_buffer[buffer_index++] = *temp_per;
        } else {
            if (buffer_index > 0) {
                num_buffer[buffer_index] = '\0';
                strcpy(temp_result, num_buffer);
                temp_result += buffer_index;
                *(temp_result++) = ' ';
                buffer_index = 0;
            }

            if (isOperator(*temp_per)) {
                // 运算符处理逻辑
                char *operatorStr = (char *)malloc(2);
                operatorStr[0] = *temp_per;
                operatorStr[1] = '\0';
                if (IsEmpty(oper_stack)) {
                    Push(oper_stack, operatorStr);
                } else {
                    if (*temp_per == '(') {
                        Push(oper_stack, operatorStr);
                    } else if (*temp_per == ')') {
                        while (!IsEmpty(oper_stack) && Top(oper_stack)[0] != '(') {
                            char *oldElem = Pop(oper_stack);
                            *(temp_result++) = oldElem[0];
                            *(temp_result++) = ' ';
                            free(oldElem);
                        }
                        free(Pop(oper_stack));
                    } else {
                        while (!IsEmpty(oper_stack) && isHigher(Top(oper_stack)[0], *temp_per)) {
                            char *oldElem = Pop(oper_stack);
                            *(temp_result++) = oldElem[0];
                            *(temp_result++) = ' ';
                            free(oldElem);
                        }
                        Push(oper_stack, operatorStr);
                    }
                }
            }
        }
        temp_per++;
    }

    // 输出最后一个数字
    if (buffer_index > 0) {
        num_buffer[buffer_index] = '\0';
        strcpy(temp_result, num_buffer);
        temp_result += buffer_index;
        *(temp_result++) = ' ';
    }

    while (!IsEmpty(oper_stack)) {
        char *oldElem = Pop(oper_stack);
        *(temp_result++) = oldElem[0];
        *(temp_result++) = ' ';
        free(oldElem);
    }

    DisposeStack(oper_stack);
    *temp_result = '\0';
    return result_str;
}


// 根据运算符计算两个整数
double calcuation_two_nums(double num1, double num2, const char oper) {
    if (oper == '+')
    {
        return num1 + num2;
    }
    else if (oper == '-')
    {
        return num1 - num2;
    }
    else if (oper == '*')
    {
        return num1 * num2;
    }
    else if (oper == '/')
    {
        return num1 / num2;
    }
    else if (oper == '^')
    {
        return fast_pow(num1, num2);
    }
    // 默认返回
    return 0.0;
}

double calcuationBySuffix(const char *formula) {
    // 创建一个操作数栈
    Stack operand_stack = CreateStack();
    const char *temp_formula = formula;

    while (*temp_formula != '\0') {
        if (*temp_formula == ' ') {
            temp_formula++;
            continue;
        }

        // 读取完整操作数，支持多位数和负数
        if (isdigit(*temp_formula) || (*temp_formula == '-' && isdigit(*(temp_formula + 1)))) {
            char numStr[20];  // 假设数值不超过20位
            int pos = 0;

            // 复制完整的数值到 numStr
            while (*temp_formula != ' ' && *temp_formula != '\0') {
                numStr[pos++] = *temp_formula;
                temp_formula++;
            }
            numStr[pos] = '\0';

            // 将操作数入栈
            char *operand = strdup(numStr);
            Push(operand_stack, operand);

        } else if (isOperator(*temp_formula)) {
            // 处理运算符，出栈两个操作数
            char op = *temp_formula;
            temp_formula++;

            char *num1 = Pop(operand_stack);
            char *num2 = Pop(operand_stack);

            double operand2 = atof(num1);
            double operand1 = atof(num2);

            double result = calcuation_two_nums(operand1, operand2, op);  // 计算两个数
            
            free(num1);
            free(num2);

            // 将结果转换为字符串并入栈
            char resultStr[20];
            snprintf(resultStr, sizeof(resultStr), "%.2f", result);
            char *resultCopy = strdup(resultStr);
            Push(operand_stack, resultCopy);
            free(resultCopy);
        }
    }

    // 获取最终计算结果
    char *result = Pop(operand_stack);
    double final_result = atof(result);
    free(result);

    DisposeStack(operand_stack);
    return final_result;
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
        printf("后缀表达式为：%s\n", infixToSuffix(userInput));
        printf("运算结果为：%.2f\n", result);
        printf("是否继续计算？(y/n)\n");
        char choose_ch = getchar();
        eat_line();
        if (choose_ch == 'n')
            break;
    }
    printf("程序结束！bye\n");
}