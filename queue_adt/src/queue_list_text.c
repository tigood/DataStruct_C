#include "queue_list.h"
#include <stdio.h>

int main(void) {
    // 创建一个队列
    Queue q = CreateQueue();
    if (IsEmpty(q)) {
        puts("该队列为空！");
    }
    EnQueue(q, 2);
    EnQueue(q, 4);
    if (!IsEmpty(q)) {
        puts("该队列不为空!\n");
    }
    printf("队列头元素为：%d\n", Front(q));
    printf("队列尾部元素为：%d\n", Rear(q));
    printf("%d走了\n", FrontAndDequeue(q));
    printf("%d走了\n", FrontAndDequeue(q));
        if (IsEmpty(q)) {
        puts("该队列为空！");
    }

    return 0;
}