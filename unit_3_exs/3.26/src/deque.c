#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

// 辅助函数：检测队列参数合法性
void arg_is_null(Deque deque) {
    if (deque == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }
}

// 初始化双端队列
void init_deque(Deque *deque) {
    // 检测参数合法性
    if (deque == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    // 为该双端队列开辟空间
    *deque = (Deque)malloc(sizeof(struct DequeRecord));

    // 判断空间是否正确开辟
    if (*deque == NULL) {
        fprintf(stderr, "双端队列空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化双端队列
    (*deque)->p_front = NULL;
    (*deque)->p_rear = NULL;
}

// 清空双端队列
void empty_deque(Deque deque) {
    // 参数合法性检测
    arg_is_null(deque);

    // 清除元素
    while (!is_empty(deque)) {
        pop(deque);
    }
}

// 判断队列是否为空
bool is_empty(Deque deque) {
    // 参数合法性检测
    arg_is_null(deque);

    return deque->p_front == NULL;
}

// 销毁一个双端队列
void dispose_deque(Deque deque) {
    // 参数合法性检测
    arg_is_null(deque);

    // 清空双端队列
    empty_deque(deque);

    // 清除队列历程
    free(deque);
}

// 将新项插入到双端队列的前端
void push(ElementType elem, Deque deque) {
    // 参数合法性检测
    arg_is_null(deque);

    // 创建一个新节点
    ptrToNode newNode = (ptrToNode)malloc(sizeof(struct Node));

    // 判断新节点是否开辟成功
    if (newNode == NULL) {
        fprintf(stderr, "新节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化新节点
    newNode->elem = elem;
    newNode->next = NULL;
    newNode->prev = NULL;

    // 将新节点插入
    // 该队列是否为空
    if (is_empty(deque)) {
        // 如果队列为空，首尾节点都需要更新
        // deque->p_front = newNode;
        deque->p_rear = newNode;
    } else {
        // 如果队列不为空，则需要插入到头部
        deque->p_front->prev = newNode;
        newNode->next = deque->p_front;
        // deque->p_front = newNode;
    }
    // 无论是否为空，都需要更新头节点，所以提取到这里
    deque->p_front = newNode;
}

// 从双端队列中删除前端项并且将其返回
ElementType pop(Deque deque) {
    // 检测参数合法性
    arg_is_null(deque);

    // 如果队列为空就报错退出
    if (is_empty(deque)) {
        fprintf(stderr, "队列为空！弹出元素失败！\n");
        exit(EXIT_FAILURE);
    }

    // 记录将要被弹出的元素
    ElementType deleted_elem = deque->p_front->elem;
    ptrToNode deleted_node = deque->p_front;

    // 将该元素弹出
    // 更新头节点
    deque->p_front = deque->p_front->next;
    // 判断是否还有剩余节点
    if (deque->p_front) {
        // 走到这里说明还有剩余节点
        // 更新该节点的前置指针
        deque->p_front->prev = NULL;
    } else {
        // 走到这里说明队列为空了，更新尾节点
        deque->p_rear = NULL;
    }

    // 释放第一个节点
    free(deleted_node);

    // 返回被删除的元素
    return deleted_elem;
}

// 将新项插入到双端队列的尾端
void inject(ElementType elem, Deque deque) {
    // 检测参数合法性
    arg_is_null(deque);

    // 构造新节点
    ptrToNode newNode = (ptrToNode)malloc(sizeof(struct Node));

    // 检测新节点空间是否开辟成功
    if (newNode == NULL) {
        fprintf(stderr, "节点开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化新节点
    newNode->elem = elem;
    newNode->prev = NULL;
    newNode->next = NULL;

    // 考虑插入新节点
    // 判断队列是否为空
    if (is_empty(deque)) {
        // 如果队列为空，则更新头尾节点
        deque->p_front = newNode;
        // deque->p_rear = newNode;
    } else {
        // 如果队列不为空，则仅仅更新尾节点
        deque->p_rear->next = newNode;
        newNode->prev = deque->p_rear;
        // deque->p_rear = newNode;
    }
    // 无论是否为空都需要更新尾节点
    deque->p_rear = newNode;
}

// 从双端队列中删除尾端项并将其返回
ElementType eject(Deque deque) {
    // 检查参数合法性
    arg_is_null(deque);

    // 如果队列为空就报错退出
    if (is_empty(deque)) {
        fprintf(stderr, "队列为空，弹出元素失败！\n");
        exit(EXIT_FAILURE);
    }

    // 记录要被弹出的元素
    ElementType deleted_elem = deque->p_rear->elem;
    ptrToNode deleted_node = deque->p_rear;

    // 移动尾节点
    deque->p_rear = deque->p_rear->prev;

    // 判断是否还有剩余元素
    if (deque->p_rear) {
        // 走到这里说明还有剩余元素
        deque->p_rear->next = NULL;
    } else {
        // 走到这里说明没有剩余元素了
        deque->p_front = NULL;
    }

    // 释放该节点
    free(deleted_node);

    return deleted_elem;
}