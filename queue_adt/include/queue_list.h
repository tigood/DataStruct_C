/*
队列的链表实现
*/
#ifndef _QUEUE_LIST_H
#define _QUEUE_LIST_H
#include <stdbool.h>
typedef int ElementType;

struct Node;
struct QueueRecord;
typedef struct Node *PtrToNode;
typedef struct QueueRecord *Queue;

struct Node {
    ElementType elem;
    PtrToNode next;
};

struct QueueRecord{
    PtrToNode pFront;
    PtrToNode pRear;
};

// 创建一个队列
Queue CreateQueue(void);

// 销毁一个队列
void DisposeQueue(Queue);

// 清空一个队列
void MakeEmpty(Queue);

// 判断队列是否为空
bool IsEmpty(Queue);

// 返回队首元素
ElementType Front(Queue);

// 返回队尾元素
ElementType Rear(Queue);

// 弹出队首元素
void DeQueue(Queue);

// 返回并弹出队首元素
ElementType FrontAndDequeue(Queue);

// 将一个元素压入队尾
void EnQueue(Queue, ElementType);

// 辅助函数
void QueueIsNull(Queue q);

#endif