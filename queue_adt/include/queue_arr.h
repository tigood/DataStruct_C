/*
队列的数组实现
*/
#ifndef _QUEUE_ARR_H
#define _QUEUE_ARR_H
#define MINLEN 5
#include <stdbool.h>

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;

struct QueueRecord{
    int capacity;
    int front;
    int rear;
    int size;
    ElementType *array;
};

// 创建一个空的队列
// 前置条件：传入一个整形，代表要创建的队列的长度
// 后置条件：返回一个队列
Queue CreateQueue(int);

// 释放一个队列例程
// 前置条件：传入一个有效的队列
// 后置条件：将该队列销毁，内存释放
void DisposeQueue(Queue);

// 检测队列是否已满
// 前置条件：传入一个有效的队列
// 后置条件：如果队列已满，返回true，否则返回false
bool IsFull(Queue);

// 检测当前队列是否为空
// 前置条件：传入一个有效的队列
// 后置条件：如果当前队列为空，返回true，否则返回false
bool IsEmpty(Queue);

// 将队列置为空
// 前置条件：传入一个有效的队列
// 后置条件：将该队列清空
void MakeEmpty(Queue);

// 查看队列头部元素
// 前置条件：传入一个有效的队列
// 后置条件：返回该队列的头部元素
ElementType Front(Queue);

// 查看队尾元素
// 前置条件：传入一个有效的队列
// 后置条件：返回尾部元素
ElementType Rear(Queue);

// 在队列头弹出一个元素
// 前置条件：传入一个有效的队列
// 后置条件：该队列头部元素被弹出，长度-1
void DeQueue(Queue);

// 返回队列头部元素并且弹出
// 前置条件：传入一个有效的队列
// 后置条件：该队列头部元素被弹出，长度-1,并将该值返回
ElementType FrontAndDeQueue(Queue);

// 在队列尾部加入一个元素
// 前置条件：传入一个有效的队列，和一个元素值
// 后置条件：将该元素值压入队列的尾部
void EnQueue(Queue, ElementType);

// 辅助函数
// 前置条件：传入一个队列
// 后置条件：如果这个队列为NULL，则退出程序
void QueueIsNull(Queue q);

#endif