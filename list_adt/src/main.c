/*
单向list测试函数
*/
#include <stdio.h>
#include "list.h"

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

int main()
{
    exchange_elem_text();
    return 0;
}
