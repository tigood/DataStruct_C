/*
实现采用惰性删除的链表
*/
#ifndef _LIST_LAZY_DEL
#define _LIST_LAZY_DEL
#include <stdbool.h>

struct Node;
struct ListRecord;

typedef int Item;  // 元素
typedef struct Node *ptrToNode;  // 指向节点的指针
typedef struct ListRecord *List;  // 链表

struct Node {
    // 单向链表：一个节点包含元素值本身和指向下一个节点的指针
    Item element;
    ptrToNode next;
    bool is_del;  // 判断当前元素是否被删除的标志
};

struct ListRecord {
    ptrToNode p_front;  // 头节点
    int all_item_counts;  // 总元素的数量
    int deleted_item_counts;  // 被标记为已删除的元素的数量
    int normal_item_counts;  // 正常存在的元素的数量
};

// 方法

// 辅助函数：检测参数合法性
void arg_is_null(List);

// 初始化一个链表
// 前置条件：传入一个指向链表的指针
// 后置条件：初始化该链表
void init_list(List *);

// 清空一个链表
// 前置条件：传入一个链表
// 后置条件：清除这个链表中的所有元素
void empty_list(List);

// 销毁一个链表
// 前置条件：传入一个链表的指针
// 后置条件：将该链表例程销毁，并将该指针置为NULL
void dispose_list(List *);

// 将一个元素插入到链表的头部
// 前置条件：传入一个指定元素和一个目标链表
// 后置条件：该元素被插入到链表的头部
void insert_list_header(Item, List);

// 将一个元素插入到指定的位置
// 前置条件：传入一个指定元素和一个目标链表以及一个合理的位置
// 后置条件：该指定元素被插入到合理的位置
bool insert_list_by_postion(Item, List, int);

// 遍历链表删除其中被标记为已删除的元素
// 前置条件：传入一个链表
// 后置条件：将该链表中的所有被标记为删除的元素删除掉
void rm_deleted_items(List);

// 懒惰删除链表中的一个指定元素
// 前置条件：传入一个指定元素和一个链表
// 后置条件：该元素被标记为已删除，如果符合条件就删除。
void delete_item_lazy(Item, List);

// 判断链表是否为空
// 前置条件：传入一个链表
// 后置条件：如果该链表为空返回true，否则返回false
bool is_empty(List);

// 判断链表内是否还有正常元素
// 前置条件：传入一个链表
// 后置条件：如果该链表正常元素为空返回true，否则返回false
bool is_empty_nomal(List);

// 遍历打印链表内容
// 前置条件：传入一个链表
// 后置条件：在一行中打印这个链表
void print_list(List);

#endif