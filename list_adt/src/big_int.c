/*
任意精度整数包  大数的实现
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_DIGITS 5000  // 设定最大整数的位数

typedef struct {
    int digits[MAX_DIGITS]; // 每一个元素代表该大数的一个位数
    int length; // 大数的位数长度
} BigInt;

// 初始化一个大数
// 前置条件：传入一个指向的大数的指针
// 后置条件：在该指向的空间开辟空间
void InitBigInt(BigInt *);

// 将一个整数转换为大数形式
// 前置条件：传入一个指向大数的指针，和一个整形
// 后置条件：将该整形转换为大数，存储在指针所指向的地方
void IntToBigInt(BigInt *, int);

// 统计大整数中0-9的分布
// 前置条件：传入一个指向大数的指针，和一个指向整形数组的指针
// 后置条件：将该大树中位数的0-9数字的分布结果存储在整形数组中
void CountDigits(BigInt *, int *);

// 大整数的乘积
// 前置条件：传入一个指向大数的指针和一个整形
// 后置条件：将大数与该整形的乘积计算之后的结果存储在大数中
void Multiply(BigInt *, int);

// 快速幂
void Power(BigInt *, int base, int exp);

void main(void) {

    return 0;
}

void InitBigInt(BigInt *num) {
    if (num == NULL) return;  // 防止空指针传入
    memset(num->digits, 0, sizeof(int) * MAX_DIGITS);  // 将分配的空间清零
    num->length = 1;
}

void IntToBigInt(BigInt *num, int value) {
    InitBigInt(num);
    num->length = 0;
    while (value > 0) {
        num->digits[num->length++] = value % 10;
        value /= 10;
    }
    // 处理value值为0的结果
    if (num->length == 0)
        num->length = 1;
}

void CountDigits(BigInt *num, int *counts) {
    // 初始化counts
    memset(counts, 0, sizeof(int) * 10);
    for (int i = 0; i < num->length; i++) {
        counts[num->digits[i]]++;
    }
}

// 大数的乘积运算
void Multiply(BigInt *num, int value) {
    int carry = 0;
    for (int i = 0; i < num->length; i++) {
        int product = num->digits[i] * value + carry;
        num->digits[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0) {
        num->digits[num->length++] = carry % 10;
        carry /= 10;
    }
}

// 快速幂：计算 base^exp
void Power(BigInt *result, int base, int exp) {
    SetValue(result, 1);  // 初始值为 1
    BigInt baseValue;
    SetValue(&baseValue, base);  // 设定底数

    while (exp > 0) {
        if (exp % 2 == 1) {  // exp 是奇数时
            Multiply(result, base);
        }
        Multiply(&baseValue, base);  // 底数平方
        exp /= 2;
    }
}