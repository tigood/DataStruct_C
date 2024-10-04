/*
单向list测试函数
*/
#include <stdio.h>
#include "list.h"
#include "list_more_func.h"

void list_text(void) {
    // 单链表常规功能测试
    List mylist;
    // 初始化列表
    initList(&mylist);
    // 创建一个节点，并加入到这个链表中
    mylist->next = newNode(1);
    // 遍历链表
    forList(mylist);
    // 插入一个元素
    insertItem(2, &mylist, mylist->next);
    // 遍历链表
    forList(mylist);
    // 删除一个元素
    deleteItem(2, &mylist);
    // 遍历链表
    forList(mylist);
}

void exchange_elem_text(void) {
    // 通过指针交换元素功能测试
    List myList;
    initList(&myList);
    myList->next = newNode(1);
    insertItem(2, &myList, myList->next);
    insertItem(3, &myList, myList->next->next);
    forList(myList);
    exchangeByPtr(myList, 1);
    forList(myList);
    exchangeByPtr(myList, 2);
    forList(myList);
}

void unionListAndInterListText(void) {
    // 测试链表的交并集操作
    List l1, l2;
    initList(&l1);
    initList(&l2);
    insertItem(3, &l1, l1);
    insertItem(2, &l1, l1);
    insertItem(2, &l1, l1);
    insertItem(1, &l1, l1);

    insertItem(5, &l2, l2);
    insertItem(3, &l2, l2);
    insertItem(3, &l2, l2);
    insertItem(2, &l2, l2);
    insertItem(1, &l2, l2);
    List union_result = ListsUnion(l1, l2);
    List insert_result = ListsIntersect(l1, l2);
    printf("List1: \n");
    forList(l1);
    printf("List2: \n");
    forList(l2);
    printf("两个链表的并集：\n");
    forList(union_result);
    printf("两个链表的交集：\n");
    forList(insert_result);
    DisposeList(l1);
    DisposeList(l2);
    DisposeList(union_result);
    DisposeList(insert_result);
}

// 测试链表反转功能的实现
void ReverseListText(void) {
    List l1;
    List l2;
    initList(&l1);
    insertItem(1, &l1, l1);
    insertItem(2, &l1, l1);
    insertItem(3, &l1, l1);
    // 测试
    l2 = ReverseList(l1);
    // 输出
    printf("l1: \n");
    forList(l1);
    printf("l2: \n");
    forList(l2);
    DisposeList(l1);
    DisposeList(l2);
}

int main()
{
    // exchange_elem_text();
    // unionListAndInterListText();
    ReverseListText();
    return 0;
}
