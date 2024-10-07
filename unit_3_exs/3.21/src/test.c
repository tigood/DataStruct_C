#include "two_stacks_by_one_arr.h"
#include <stdio.h>

void test_1(void) {
    TwoStacks two_stacks;
    init_stacks(&two_stacks);

    push_1(1, &two_stacks);
    push_1(2, &two_stacks);

    push_2(3, &two_stacks);
    push_2(4, &two_stacks);

    printf("栈1弹出栈顶元素为：%d\n", pop_1(&two_stacks));
    printf("栈2弹出栈顶元素为：%d\n", pop_2(&two_stacks));
}

void test_2(void) {
    // 初始化一个栈
    TwoStacks s;
    init_stacks(&s);

    push(3, &s);
    push(2, &s);
    push(6, &s);
    push(1, &s);
    push(9, &s);

    printf("栈中的最小元素为: %d\n", find_min(&s));
}

int main(void) {
    test_2();

    return 0;
}