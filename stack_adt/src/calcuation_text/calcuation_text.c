#include "calcuation.h"
#include "ch_stack.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

int main(void) {
    // 测试函数
    char user_input[MAXLEN];
    printf("请输入一个算式：\n");
    s_gets(user_input, MAXLEN);
    char *result = infixToSuffix(user_input);
    printf("转换后为：%s\n", result);
    free(result);

    return 0;
}