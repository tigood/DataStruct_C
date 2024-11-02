//
// Created by tigood on 2024/10/31.
//

#ifndef HASH_QUAD_H
#define HASH_QUAD_H
#define MINCAL 5
typedef unsigned int Index;
typedef Index Position;
typedef int ElementType;

struct HashTbl;
typedef struct HashTbl *HashTable;

enum KindOfEntry {
    Legitimate,
    Empty,
    Deleted
};

typedef struct HashEntry {
    ElementType elem;
    enum KindOfEntry info;
} Cell;

struct HashTbl {
    int table_size;
    Cell *table;
};

// 创建一个哈希表
// 前置条件：传入该表的长度
// 后置条件：创建一个哈希表并返回
HashTable create_hash_table_quad(int);

// 销毁一个哈希表
// 前置条件：传入一个指定的哈希表指针
// 后置条件：该指针指向的哈希表被销毁，并将指针重置为null
void destroy_hash_table_quad(HashTable *);

// 根据值找到目标节点
// 前置条件：传入目标哈希表，和一个指定值
// 后置条件：找到指定值的元素之后，返回该元素的位置
Position find_elem_hash_table_quad(HashTable, ElementType);

// 向指定的哈希表中插入一个指定元素
// 前置条件：传入指定的哈希表，和一个指定的元素
// 后置条件：该元素被插入到哈希表中
void insert_elem_hash_table_quad(HashTable, ElementType);

// 取出哈希表单元格中的值
// 前置条件：传入一个指定的哈希表，和一个指定的位置
// 后置条件：返回该位置的值
ElementType retrieve_elem_hash_table_quad(HashTable, Position);

// 再散列
// 前置条件：传入一个指定的哈希表
// 后置条件：返回这个再散列之后的哈希表
HashTable rehash_hash_table_quad(HashTable);

#endif //HASH_QUAD_H
