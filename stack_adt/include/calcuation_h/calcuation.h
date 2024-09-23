/*
使用栈的应用：
    实现一个计算器
*/
#ifndef _CALCUATION_H
#define _CALCUATION_H
#include <stdbool.h>
#include <stdio.h>


/*
辅助函数
*/
// 手动封装字符串的读取
char *s_gets(char *st, int n);

// 读取残留的回车
inline void eat_line(void) {
    while (getchar () != '\n')
        continue;
}

/*
方法
*/

// 前缀到中缀的转换器
char *perToSuffix(const char *);

// 根据后缀表达式计算结果
int calcuationBySuffix(const char *);

// 读取用户输入的算式
char *getUserInput(void);

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


#endif