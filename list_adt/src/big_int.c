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
void InitBigInt(BigInt *);

// 将一个整数转换为大数形式
void IntToBigInt(BigInt *, int);

// 统计大整数中0-9的分布
void CountDigits(BigInt *, int *);

// 大整数的乘积
void Multiply(BigInt *, int);

// 快速幂
void Power(BigInt *, int base, int exp);

void main(void) {

    return 0;
}

void InitBigInt(BigInt *num) {
    // 将大数数组中的每一项初始化为0
    memset(num->digits, 0, sizeof(num->digits));
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