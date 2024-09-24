#include "queue_arr.h"
#include <stdio.h>
#include <stdlib.h>

// 辅助函数
void QueueIsNull(Queue q) {
    if (q == NULL) {
        fprintf(stderr, "该队列为NULL！\n");
        exit(EXIT_FAILURE);
    }
}

// 创建一个指定长度的队列
Queue CreateQueue(int MaxSize) {
    // 判断指定的长度是否符合最小长度
    if (MaxSize < MINLEN) {
        fprintf(stderr, "您指定的长度太小了！\n");
        exit(EXIT_FAILURE);
    }
    // 创建一个队列
    Queue q = (Queue)malloc(sizeof(struct QueueRecord));
    if (q == NULL) {
        fprintf(stderr, "队列开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 为数组开辟空间
    q->array = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    if (q->array == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 初始化属性值
    q->rear = 0;
    q->front = 0;
    q->capacity = MaxSize;
    q->size = 0;
    return q;
}

// 释放一个栈例程
void DisposeQueue(Queue q) {
    QueueIsNull(q);
    if (q->array != NULL) {
        free(q->array);
    }
    free(q);
}

// 判断队列是否已满
bool IsFull(Queue q) {
    QueueIsNull(q);
    return q->size == q->capacity;
}

// 判断队列是否为空
bool IsEmpty(Queue q) {
    QueueIsNull(q);
    return q->size == 0;
}

// 将队列置为空
void MakeEmpty(Queue q) {
    q->size = 0;
    q->front = 0;
    q->rear = 0;
}

// 返回队首元素
ElementType Front(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        return q->array[q->front];
    } else {
        fprintf(stderr, "队列为空！\n");
        exit(EXIT_FAILURE);
    }
}

// 返回队尾元素
ElementType Rear(Queue q) {
    QueueIsNull(q);
    // 由于q->rear存储的是尾元素的下一个位置的索引，所以这里需要q->rear的前一个位置的索引
    if (!IsEmpty(q)) {
        return q->array[(q->rear - 1 + q->capacity) % q->capacity];
    } else {
        fprintf(stderr, "队列为空！\n");
        exit(EXIT_FAILURE);
    }
}

// 在队头弹出一个元素
void DeQueue(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        // 如果队列不为空
        q->front = (q->front + 1) % q->capacity;
        q->size--;
    } else {
        fprintf(stderr, "队列为空！\n");
        exit(EXIT_FAILURE);
    }
}

// 返回队头元素，并将它弹出
ElementType FrontAndDeQueue(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        // 如果队列不为空
        ElementType front_elem = Front(q);
        DeQueue(q);
        return front_elem;
    } else {
        fprintf(stderr, "队列为空！\n");
        exit(EXIT_FAILURE);
    }
}

void EnQueue(Queue q, ElementType elem) {
    QueueIsNull(q);
    if (!IsFull(q)) {
        // 如果队列没有满
        q->array[q->rear] = elem;
        q->rear = (q->rear + 1) % q->capacity;
        q->size++;
    } else {
        fprintf(stderr, "队列已满！\n");
        exit(EXIT_FAILURE);
    }
}