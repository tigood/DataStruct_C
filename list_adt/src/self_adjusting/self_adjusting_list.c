#include "self_adjusting_list.h"
#include <stdio.h>
#include <stdlib.h>

// 参数合法性检测
void ArgIsNull(SelfAdjustList sa_list) {
    if (sa_list == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }
}

// 初始化一个自调节表
void InitSelfAdjustList(SelfAdjustList *sa_list) {
    ArgIsNull(*sa_list);

    // 开辟空间
    *sa_list = (SelfAdjustList)malloc(sizeof(struct SelfAdjustListRecord));
    if (*sa_list == NULL) {
        // 走到这里说明空间开辟失败
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 创建头节点
    PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    (*sa_list)->pFront = newNode;
    (*sa_list)->length = 0;
}

// 清空一个自调节表
void EmptyTheAdjustList(SelfAdjustList sa_list) {
    // 检测参数的合法性
    ArgIsNull(sa_list);
    PtrToNode temp = sa_list->pFront->next;
    PtrToNode curr;
    while (temp != NULL)
    {
        curr = temp;
        temp = temp->next;
        free(curr);
    }
    sa_list->pFront->next = NULL;
    sa_list->length = 0;
}

// 释放一个表的例程
void DisposeTheAdjusList(SelfAdjustList sa_list) {
    // 检测参数合法性
    ArgIsNull(sa_list);

    EmptyTheAdjustList(sa_list);
    // 释放头节点
    if (sa_list->pFront != NULL) {
        free(sa_list->pFront);
        sa_list->pFront = NULL;
    }
    // 释放例程
    free(sa_list);
}

bool InsertToHeaderOfList(ElementType elem, SelfAdjustList sa_list) {
    ArgIsNull(sa_list);

    // 创建一个新节点
    PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        return false;
    }
    newNode->elem = elem;
    newNode->next = NULL;

    // 判断当前自调节表是否为空
    if (IsEmpty(sa_list)) {
        // 如果为空，直接添加在头节点后面
        sa_list->pFront->next = newNode;
    } else {
        // 如果不为空就在头部之后插入
        newNode->next = sa_list->pFront->next;
        sa_list->pFront->next = newNode;
    }
    sa_list->length++;

    return true;
}

bool Find(ElementType target, SelfAdjustList sa_list) {
    ArgIsNull(sa_list);

    if (IsEmpty(sa_list)) {
        printf("该表为空，为查找到目标元素\n");
        // 如果为空，就返回false
        return false;
    }

    PtrToNode prev = sa_list->pFront;  // 定义指向前驱节点的指针
    PtrToNode curr = sa_list->pFront->next;  // 定义指向当前节点的指针

    // 遍历链表
    while (curr != NULL) {
        if (curr->elem == target) {
            break;
        }
        prev = curr;  // 更新前驱指针
        curr = curr->next;  // 更新当前指针
    }

    if (curr == NULL) {
        // 走到这里说明没有找到指定元素
        return false;
    }

    // 判断目标节点是否已经在表头，如果在就不需要移动了
    if (prev == sa_list->pFront) {
        return true;
    }

    // 断开目标节点，将目标节点插入表头
    prev->next = curr->next;
    curr->next = sa_list->pFront->next;
    sa_list->pFront->next = curr;

    return true;
}

ElementType Front(SelfAdjustList sa_list) {
    ArgIsNull(sa_list);

    return sa_list->pFront->next->elem;
}

bool IsEmpty(SelfAdjustList sa_list) {
    ArgIsNull(sa_list);

    return sa_list->length == 0;
}