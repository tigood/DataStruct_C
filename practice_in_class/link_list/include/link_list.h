/*
单链表实现的头文件(带头节点的实现)
*/
#ifndef _LINK_LIST
#define _LINK_LIST
#include <stdbool.h>

struct Node;

typedef int ElementType;
typedef struct Node *ptrToNode;
typedef struct Node *LinkList;

struct Node {
    ElementType elem;  // 节点值
    ptrToNode next;
};

// 参数合法性检测
void arg_is_null(void *);

// 检测空间是否正常开辟
void check_malloc(void *);

// 以返回值的形式初始化一个链表
LinkList init_list_return(void);

// 以指针的形式初始化一个链表
void init_list(LinkList *);

// 创建单链表，批量插入并链接一批节点。头插法
// 前置条件：传入一个链表，和要插入的元素数量
// 后置条件：如果链表创建成功则，返回true，否则返回false
bool create_list_front(LinkList, int);

// 创建单链表，批量插入一组节点。尾插法
// 前置条件：传入一个链表，和要插入的元素数量
// 后置条件：如果链表创建成功，返回true，否则返回false
bool create_list_rear(LinkList, int);

// 创建单链表，随机生成一组数组插入链表，使用尾插法
// 前置条件：传入一个链表，和要插入的元素数量
// 后置条件：如果链表创建成功返回true，否则返回false
bool create_list_rear_random(LinkList, int);

// 判断链表是否为空
// 前置条件：传入一个链表
// 后置条件：如果链表为空返回true，否则返回false
bool is_empty(LinkList);

// 打印单链表
// 前置条件：传入一个指定的链表
// 后置条件：将该链表的内容逐一打印出来
bool print_list(LinkList);

// 单链表位置查找，按位置查找
// 前置条件：传入一个链表，指定的位置，和查找结果的存储位置指针
// 后置条件：如果查找成功返回true， 否则返回false，没有查找成功时结果位置的值是未定义的
bool get_elem_by_position(LinkList, int, ElementType *);

// 根据元素值在单链表中查找元素
// 前置条件：传入一个目标链表，和要查找的元素
// 后置条件：如果成功查找到了该元素，返回该元素的位置，否则返回0
int find_node_by_value(LinkList, ElementType);

// 将指定元素插入到指定位置元素的前面
// 前置条件：传入一个目标链表，插入的位置，和插入元素
// 后置条件：如果插入成功就返回true，否则返回false
bool insert_node_by_position(LinkList, int, ElementType);

// 按位置删除元素
// 前置条件：传入一个目标链表，和指定位置，以及指向被删除元素要存储的位置的指针
// 后置条件：如果删除成功返回true，否则返回false，删除失败时第三个参数指针指向位置的数值时未定义的
bool delete_node_by_position(LinkList, int, ElementType *);

// 按数值删除元素，删除找到的第一个元素
// 前置条件：传入一个目标链表，和目标元素值
// 后置条件：如果删除成功就返回true，否则返回false
bool delete_node_by_value(LinkList, ElementType);

// 按数值删除，删除链表中所有与指定数值相等的元素
// 前置条件：传入一个目标链表，和目标元素值
// 后置条件：如果删除成功就返回true，否则返回false
bool delete_nodes_by_value(LinkList, ElementType);

// 合并链表
// 前置条件：传入两个按值递增排列
// 后值条件：返回合并之后的链表
LinkList combine_lists(LinkList, LinkList);

// 逆置链表
// 前置条件：传入一个指定链表
// 后置条件：该链表被逆置
void reverse_list(LinkList);

// 销毁一个链表
// 前置条件：传入一个指定链表的指针
// 后置条件：该链表被销毁
bool dispose_list(LinkList *);

// 返回链表的长度
// 前置条件：传入一个指定链表
// 后置条件：返回该链表的长度
int list_length(LinkList);

#endif