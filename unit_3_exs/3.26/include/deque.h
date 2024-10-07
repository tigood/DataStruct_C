/*
双端队列的链表实现   （没有使用头尾哨兵节点）
*/
#include <stdbool.h>

struct Node;
struct DequeRecord;

typedef int ElementType;
typedef struct Node *ptrToNode;
typedef struct DequeRecord *Deque;

struct Node {
    ElementType elem;  // 节点值
    ptrToNode next;  // 指向下一个节点的指针
    ptrToNode prev;  // 指向上一个节点的指针
};

struct DequeRecord {
    ptrToNode p_front;  // 指向头节点的指针
    ptrToNode p_rear;  // 指向尾节点的指针
};

// 辅助函数：检测队列参数合法性
void arg_is_null(Deque);

// 初始化一个双端队列
// 前置条件：传入一个指向双端队列的指针
// 后置条件：初始化该双端队列
void init_deque(Deque *);

// 清空一个队列
// 前置条件：传入一个双端队列
// 后置条件：该双端队列被清空
void empty_deque(Deque);

// 判断一个队列是否为空
bool is_empty(Deque);

// 销毁一个队列
// 前置条件：传入一个双端队列
// 后置条件：该双端队列被销毁
void dispose_deque(Deque);

// 将新项插入到双端队列的前端
void push(ElementType, Deque);

// 从双端队列中删除前端项并且将其返回
ElementType pop(Deque);

// 将新项插入到双端队列的尾端
void inject(ElementType, Deque);

// 从双端队列中删除尾端项并将其返回
ElementType eject(Deque);