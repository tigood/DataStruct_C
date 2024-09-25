#include "queue_list.h"
#include <stdio.h>
#include <stdlib.h>

// 辅助函数，判断队列不为NULL，如果队列为NULL，则退出
void QueueIsNull(Queue q) {
    if (q == NULL) {
        fprintf(stderr, "传参错误！\n");
        exit(EXIT_FAILURE);
    }
}

// 创建一个队列
Queue CreateQueue(void) {
    Queue q = (Queue)malloc(sizeof(struct QueueRecord));
    if (q == NULL) {
        fprintf(stderr, "队列空间分配失败！\n");
        exit(EXIT_FAILURE);
    }
    // 创建一个节点
    PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "节点空间分配失败！\n");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    q->pFront = newNode;
    q->pRear = newNode;
    return q;
}

// 销毁一个队列
void DisposeQueue(Queue q) {
    QueueIsNull(q);
    PtrToNode current = q->pFront->next;
    PtrToNode temp;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    // 释放头节点
    free(q->pFront);
    // 释放队列例程
    free(q);
}

// 清空一个队列
void MakeEmpty(Queue q) {
    QueueIsNull(q);
    // 当队列不为空时，将元素逐一弹出
    while (!IsEmpty(q)) {
        DeQueue(q);
    }
}

// 判断队列是否为空
bool IsEmpty(Queue q) {
    QueueIsNull(q);
    return q->pFront->next == NULL;
}

// 返回队首元素
ElementType Front(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        return q->pFront->next->elem;
    }
}

// 返回队尾元素
ElementType Rear(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        return q->pRear->elem;
    }
}

// 弹出队首元素
void DeQueue(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        PtrToNode temp = q->pFront->next;
        q->pFront->next = temp->next; // 更新队首
        if (q->pFront->next == NULL) { // 如果队列变空
            q->pRear = q->pFront; // 更新 pRear
        }
        free(temp); // 释放内存
    } else {
        fprintf(stderr, "该队列为空，不能进行弹出操作！\n");
        exit(EXIT_FAILURE);
    }
}

// 返回并弹出队首元素
ElementType FrontAndDequeue(Queue q) {
    QueueIsNull(q);
    if (!IsEmpty(q)) {
        // 记录要弹出的元素的值
        ElementType oldElem = Front(q);
        // 将队首元素弹出
        DeQueue(q);
        return oldElem;
    } else {
        fprintf(stderr, "队列为空，不能弹出元素\n");
        exit(EXIT_FAILURE);
    }
}

// 将一个元素压入队尾
void EnQueue(Queue q, ElementType elem) {
    QueueIsNull(q);
    // 创建一个新节点
    PtrToNode newElem = (PtrToNode)malloc(sizeof(struct Node));
    if (newElem == NULL) {
        fprintf(stderr, "新节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    newElem->elem = elem;
    newElem->next = NULL;
    // 如果队列为空
    if (IsEmpty(q)) {
        q->pFront->next = newElem;
    } else {
        q->pRear->next = newElem;
    }
    q->pRear = newElem;
}