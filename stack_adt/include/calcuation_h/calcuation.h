/*
使用栈的应用：
    实现一个计算器
*/
#ifndef _CALCUATION_H
#define _CALCUATION_H
#include <stdbool.h>
#include <stdio.h>
#define MAXLEN 100


/*
辅助函数
*/
// 手动封装字符串的读取
char *s_gets(char *st, int n);

// 读取残留的回车
void eat_line(void);

/*
方法
*/

// 中缀到后缀的转换器
// 前置条件：传入一个中缀算式
// 后值条件：返回该算式的后缀形式（字符串）
char *infixToSuffix(const char *);

// 根据后缀表达式计算结果
// 前置条件：传入一个后缀表达式
// 后置条件：返回这个后缀表达式计算出来的值
double calcuationBySuffix(const char *);

// 读取用户输入的算式
char *getUserInput(char *st, int n);

// 判断两个运算符的优先级
// 前置条件：传入两个运算符字符
// 后值条件：如果第一个运算字符的优先级大于等于第二个运算字符，返回true。否则返回false
bool isHigher(char, char);

// 判断该字符串是否是一个个该程序所支持的运算符
// 前置条件：传入一个字符
// 后值条件：如果该字符是一个所支持的运算符，则返回true，否则返回false
bool isOperator(char);

// 获取运算符优先级
// 前置条件：传入一个运算符
// 后置条件：返回这个运算符的优先级数字形式
int getPrecedence(char ch);

// 根据两个操作数和一个运算符进行运算
// 前置条件：传入两个操作数和一个运算符
// 后置条件：返回计算结果的整形
double calcuation_two_nums(double num1, double num2, const char oper);

// 系统运行函数
void cal_sys_run(void);

#endif