/*
单向list测试函数
*/
#include <stdio.h>
#include "list.h"

int main()
{
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

    return 0;
}
