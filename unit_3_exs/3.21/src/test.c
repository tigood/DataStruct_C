#include "two_stacks_by_one_arr.h"
#include <stdio.h>

int main(void) {
    TwoStacks two_stacks;
    init_stacks(&two_stacks);

    push_1(1, &two_stacks);
    push_1(2, &two_stacks);

    push_2(3, &two_stacks);
    push_2(4, &two_stacks);

    printf("栈1弹出栈顶元素为：%d\n", pop_1(&two_stacks));
    printf("栈2弹出栈顶元素为：%d\n", pop_2(&two_stacks));

    return 0;
}