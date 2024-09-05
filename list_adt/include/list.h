#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>
typedef int Item;  // 元素
struct Node;                     // 节点
typedef struct Node *ptrToNode;  // 指向节点的指针
typedef ptrToNode List;
typedef ptrToNode Position;

struct Node {
    // 单向链表：一个节点包含元素值本身和指向下一个节点的指针
    Item element;
    Position next;
};

// 方法

// 检测链表是否为空
bool isEmpty(const List*);

// 初始化一个节点
Position newNode(Item);

// 检测当前节点是否为尾节点
bool isLast(const Position, const List *);

// 将列表初始化
void initList(List *);

// 根据元素值查找节点
Position find(Item, List *);

// 查找目标节点的前一个位置
Position findPrev(Item, List *);

// 删除一个目标节点
bool deleteItem(Item, List *);

// 插入一个元素
bool insertItem(Item, List *, Position);

// 返回链表头部元素
Position header(List);

// 返回头部元素值
Item first(List);

// 检索元素值
Item retrieve(Position);

// 遍历一个链表
void forList(const List);
#endif
