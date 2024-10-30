//
// Created by tigood on 2024/10/30.
//

#ifndef HASH_SEP_H
#define HASH_SEP_H
#include <stdbool.h>
#define MINSIZE 5   // 定义哈希表的最小长度

typedef int ElementType;
typedef unsigned int Index;
struct ListNode;
typedef struct ListNode *Position;
typedef Position List;

struct HashTbl;
typedef struct HashTbl *HashTable;

struct ListNode {
    ElementType elem;
    Position next;
};

struct HashTbl {
    int table_size;
    List *the_lists;
};

// 创建一个哈希表
// 前置条件：传入指定的哈希表长度
// 后置条件：如果指定长度合理，就返回成功创建的哈希表
HashTable create_hash_table(int);

// 销毁一个哈希表
// 前置条件：传入一个指定的哈希表的指针
// 后置条件：销毁这个哈希表
void destroy_hash_table(HashTable *);

// 创建一个空链表
// 前置条件：
// 后置条件：返回一个带有头节点的空链表
List create_empty_list(void);

// 查找指定元素
// 前置条件：传入要搜索的哈希表，和目标元素
// 后置条件：如果搜索到之后，就返回指向该节点的指针，否则返回NULL
Position find_elem_hash_table(HashTable, ElementType);

// 插入一个指定的元素
// 前置条件：传入目标哈希表，和要插入的目标值
// 后置条件：如果该元素不存在就插入，如果元素已经存在就什么也不做
void insert_elem_hash_table(HashTable, ElementType);

// 获取一个节点的值
// 前置条件：传入一个指向节点的指针
// 后置条件：返回该节点的键值
ElementType retrieve_node(Position);

// 删除一个指定的节点
// 前置条件：传入目标哈希表，和一个指定的元素
// 后置条件：如果找到该元素就将元素删除掉返回true，如果没有找到就返回false
bool delete_node_hash_table(HashTable, ElementType);

#endif //HASH_SEP_H
