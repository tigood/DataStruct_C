#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Deque deque;
    init_deque(&deque);

    push(2, deque);
    push(1, deque);

    inject(3, deque);
    inject(4, deque);

    printf("队列的头部元素为：%d\n", pop(deque));
    printf("队列的尾部元素为：%d\n", eject(deque));

    return 0;
}