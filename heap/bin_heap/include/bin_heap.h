/*
使用数组实现的一个基本二叉堆，即优先队列
 */
#ifndef BIN_HEAP_H
#define BIN_HEAP_H
#define MINSIZE 5
#define MINDATA -666666
#define MAXDATA 666666
#include <stdlib.h>
#include <stdbool.h>

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;  // 优先队列
typedef int ElementType;

struct HeapStruct {
	int capacity;   // 二叉堆的容量
	int size;   // 二叉堆的大小
	ElementType *elements;  
};

// 初始化一个优先队列（即二叉堆）
// 前置条件：传入一个二叉堆的大小
// 后置条件：创建一个二叉堆并返回指针
PriorityQueue init_priority_queue(int max_elems);

// 销毁一个优先队列
// 前置条件：传入一个优先队列
// 后置条件：该队列例程被销毁
void destroy_priority_queue(PriorityQueue priority_queue);

// 清空一个优先队列
// 前置条件：传入一个优先队列
// 后置条件：清空该优先队列
void empty_priority_queue(PriorityQueue priority_queue);

// 向一个优先队列中插入一个元素
// 前置条件：传入一个指定的优先队列，和一个指定的元素
// 后置条件：该元素被插入到优先队列中
void insert_elem_priority_queue(PriorityQueue priority_queue, ElementType elem);

// 删除这个二叉堆中的最小值，并返回该值
// 前置条件：传入一个指定的优先队列
// 后置条件：最小值被删除，然后该元素被返回
ElementType delete_min_priority_queue(PriorityQueue priority_queue);

// 找到二叉堆中的最小值
// 前置条件：传入一个指定的优先队列
// 后置条件：返回该优先队列中的最小值
ElementType find_min_priority_queue(PriorityQueue priority_queue);

// 判断二叉堆是否为空
// 前置条件：传入一个指定的优先队列
// 后置条件：如果该队列为空返回true，否则返回false
bool is_empty_priority_queue(PriorityQueue priority_queue);

// 判断二叉堆是否为满
// 前置条件：传入一个指定的优先队列
// 后置条件：如果该优先队列满了就返回true，否则返回false
bool is_full_priority_queue(PriorityQueue priority_queue);

void hello_world(void);

#endif