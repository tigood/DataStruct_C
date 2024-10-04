#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// 列表初始化
// 前置条件：传入一个未初始化的列表
// 后置条件：该列表被初始化
void initList(List* list) {
    // 开辟空间
    *list = (List)malloc(sizeof(struct Node));
    if (*list == NULL) {
        fprintf(stderr, "开辟空间错误！\n");
        exit(EXIT_FAILURE);
    }
    (*list)->next = NULL;
}

// 初始化一个节点
// 前置条件：传入一个元素值
// 后值条件：返回一个指向一个节点的指针
Position newNode(Item newItem) {
    // 创建一个空节点
    Position newNode = (Position)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "空间开辟错误");
        return NULL;
    }
    newNode->element = newItem;
    newNode->next = NULL;
    return newNode;
}

// 判断一个列表是否为空
// 前置条件：传入一个初始化完成的链表
// 后置条件：如果链表不为空返回true,否则返回false
bool isEmpty(const List* list) {
    return (*list)->next == NULL;
}

// 判断当前节点是否为尾节点
// 前置条件：传入一个节点指针和一个初始化的链表
// 后置条件：如果该节点为尾节点则返回true，否则返回false
bool isLast(Position node, const List* list) {
    return node->next == NULL;
}

// 将链表重置为空
// 前置条件：传入一个已经初始化的链表的指针
// 后值条件：将该列表重置为空并且返回
void makeEmpty(List* plist) {
    Position current = (*plist)->next;
    Position temp;
    while (current != NULL)
    {
        // 将临时指针指向当前的下一个位置
        temp = current->next;
        // 释放当前的空间
        free(current);
        current = temp;
    }
    // 将链表重置
    (*plist)->next = NULL;
}

// 销毁一个链表
void DisposeList(List l) {
    if (l != NULL) {
        if (!isEmpty(&l)) {
            makeEmpty(&l);
        }
        free(l);
    }
}

// 查找一个元素项
// 前置条件：传入一个元素值，和一个指向目标链表的指针
// 后值条件：返回指向第一个值为该元素的节点的指针
Position find(Item target, List* plist) {
    Position p;
    p = (*plist)->next;
    while (p != NULL && p->element != target)
    {
        p = p->next;
    }
    return p;
}

// 查找一个节点的前一个元素的位置
// 前置条件：传入一个目标元素值，和一个指向初始化的链表的指针
// 后置条件：返回一个指向节点的指针
Position findPrev(Item target, List* plist) {
    Position p;
    p = *plist;

    while (p->next != NULL && p->next->element != target) {
        p = p->next;
    }

    return p;
}

// 删除查找到的第一个指定元素
// 前置条件：传入一个目标元素值，和一个指向初始化链表的指针
// 后置条件：删除成功返回true，否则返回false
bool deleteItem(Item target, List* plist)
{
    Position p;
    // 查找到目标元素的前一个元素
    p = findPrev(target, plist);
    // 判断该元素是否为尾元素，如果是则没有找到要删除的元素
    if (isLast(p, plist))
        return false;
    // 找到目标元素的前一个元素，开始执行删除
    Position tempCell = p->next;
    p->next = tempCell->next;
    // 释放删除的元素
    free(tempCell);
    return true;
}

// 在一个指定位置之后插入一个元素
// 前置条件：传入一个元素值，一个指向已经初始化的链表的指针，一个指定的位置
bool insertItem(Item item, List* plist, Position p) {
    // 创建一个新节点
    Position node = newNode(item);
    if (node == NULL) {
        return false;
    }
    // 将节点插入
    node->next = p->next;
    p->next = node;
    return true;
}

// 返回链表头部位置
Position header(List list) {
    if (list == NULL || list->next == NULL) {
        fprintf(stderr, "链表为空或者链表为初始化！\n");
        exit(EXIT_FAILURE);
    }
    return list->next;
}

// 返回链表头部元素值
Item first(List list) {
    if (list == NULL || list->next == NULL) {
        fprintf(stderr, "链表为空或者链表未初始化！\n");
        exit(EXIT_FAILURE);
    }
    return list->next->element;
}

// 检索一个元素值
Item retrieve(Position p) {
    return p->element;
}

// 遍历一个链表
void forList(const List list) {
    if (list == NULL) {
        fprintf(stderr, "链表未初始化！\n");
        exit(EXIT_FAILURE);
    }
    if (list->next == NULL) {
        puts("链表为空！\n");
    }
    // 走到这里说明链表有数据
    printf("链表数据如下：\n");
    Position temp = list->next;
    while (temp != NULL)
    {
        printf("%d ", temp->element);
        temp = temp->next;
    }
    putchar('\n');
}

ptrToNode FindPrePtrByPos(List l, int pos) {
    if (pos <= 0) {
        return NULL;
    }
    ptrToNode result = l;
    while (pos - 1 > 0 && result != NULL)
    {
        result = result->next;
        pos--;
    }
    return result;
}

void exchangeByPtr(List l, int index) {
    // 找出该位置节点的前置节点，如果为NULL，则表示要查找的节点的位置不合理
    ptrToNode ptrPreNode = FindPrePtrByPos(l, index);
    if (ptrPreNode == NULL || ptrPreNode->next == NULL || ptrPreNode->next->next == NULL) {
        fprintf(stderr, "传入的位置不合理！\n");
        exit(EXIT_FAILURE);
    }
    ptrToNode curr = ptrPreNode->next;
    ptrToNode temp = curr->next;
    curr->next = temp->next;
    temp->next = ptrPreNode->next;
    ptrPreNode->next = temp;
}

// 通过递归实现查找元素
Position findByRecur(Item target, List *l) {
    if (l == NULL) {
        fprintf(stderr, "参数传递错误\n");
        return NULL;
    }
    Position result = *l;
    if (result->element == target) {
        return result;
    }
    if (result->next == NULL) {
        return NULL;
    }
    return findByRecur(target, &(result->next));
}

// 使用非递归的方法反转一个链表
List ReverseList(const List l) {
    if (l == NULL) {
        fprintf(stderr, "参数传递错误!\n");
        exit(EXIT_FAILURE);
    }
    // 创建并初始化一个链表
    List result;
    initList(&result);
    // 获取到第一个有效节点
    Position temp = l->next;
    while (temp != NULL) {
        insertItem(temp->element, &result, result);
        temp = temp->next;
    }
    return result;
}