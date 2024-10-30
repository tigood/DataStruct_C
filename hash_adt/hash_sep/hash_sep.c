//
// Created by tigood on 2024/10/30.
//
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "hash_sep.h"

// 哈希函数
static Index hash(const ElementType key, const int table_size) {
    return key % table_size;
}

// 检测参数是否是一个素数
static bool is_prime(const int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i <= sqrt(num); i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// 找寻当前数最近的一个素数，如果本身就是，就直接返回
static int next_prime(int num) {
    if (num <= 2) return 2;
    if (num % 2 == 0) num++; // 确保从奇数开始检测
    while (!is_prime(num)) {
        num += 2; // 只检查奇数，跳过偶数
    }
    return num;
}

// 创建一个带头节点空链表
List create_empty_list(void) {
    List list = malloc(sizeof(struct ListNode));
    if (list == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    list->next == NULL;

    return list;
}

// 创建一个哈希表
HashTable create_hash_table(int size) {
    // 检测参数合法性
    if (size < MINSIZE) {
        printf("哈希表长度最低为5！\n");
        return NULL;
    }

    // 创建哈希表
    HashTable hash_table = malloc(sizeof(struct HashTbl));
    if (!hash_table) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 为链表开辟空间
    hash_table->table_size = next_prime(size); // 计算哈希表应该的长度
    hash_table->the_lists = malloc(sizeof(struct ListNode) * hash_table->table_size);
    if (!hash_table->the_lists) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 为哈希表中的每一个单元的链表初始化表头
    for (int i = 0; i < hash_table->table_size; i++) {
        hash_table->the_lists[i] = create_empty_list();
    }
    // 返回创建的哈希表
    return hash_table;
}

// 获取一个节点的值
// 前置条件：传入一个指向节点的指针
// 后置条件：返回该节点的键值
ElementType retrieve_node(Position node) {
    if (node == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    return node->elem;
}

// 销毁一个哈希表
void destroy_hash_table(HashTable *hash_table) {
    if (*hash_table == NULL) {
        fprintf(stderr, "参数传递失败！\n");
        exit(EXIT_FAILURE);
    }

    // 销毁这个哈希表的所有单元中的头节点
    for (int i = 0; i < (*hash_table)->table_size; i++) {
        free((*hash_table)->the_lists[i]);
    }

    // 销毁这个哈希表的所有单元
    free((*hash_table)->the_lists);

    // 销毁这个哈希表结构
    free(*hash_table);

    // 将指针置空
    *hash_table = NULL;
}

// 查找指定元素
Position find_elem_hash_table(HashTable hash_table, ElementType target) {
    // 计算哈希之后的位置
    const Index index = hash(target, hash_table->table_size);
    Position curr = hash_table->the_lists[index]->next;
    while (curr != NULL && retrieve_node(curr) != target) {
        curr = curr->next;
    }

    return curr;
}

// 插入一个指定的元素
void insert_elem_hash_table(HashTable hash_table, ElementType elem) {
    // 查看当前元素是否已经存在
    Position pos = find_elem_hash_table(hash_table, elem);
    if (pos != NULL) {
        // 走到这里说明当前元素不存在，那就直接插入
        // 创建一个新节点
        Position new_node = malloc(sizeof(struct ListNode));
        if (!new_node) {
            fprintf(stderr, "空间开辟错误！\n");
            exit(EXIT_FAILURE);
        }
        /*
        * 注意，这个方法计算了两次Index，这并不好
        * 一种解决方法是，让find函数多返回一个值，这个值代表这目标元素所在的单元下标，至于如何返回方法有很多
        * 或者我们不用find，然后重新找一遍
        */
        const Index index = hash(elem, hash_table->table_size);
        new_node->elem = elem;
        new_node->next = hash_table->the_lists[index]->next;
        hash_table->the_lists[index] = new_node;
    }
    // 如果已经找到了该节点，就什么也不做
}

// 删除一个指定的节点
bool delete_node_hash_table(HashTable hash_table, ElementType target) {
    // 计算所在的单元
    const Index index = hash(target, hash_table->table_size);
    List target_list = hash_table->the_lists[index];
    Position prev_node = target_list;  // 前驱节点
    Position curr_node = target_list->next;  // 当前节点
    if (curr_node == NULL) {
        // 走到这里说明，目标单元格中没有元素，即未找到目标元素
        printf("未找到目标元素%d！\n", target);
        return false;
    }
    while (curr_node != NULL) {
        if (retrieve_node(curr_node) == target) {
            // 走到这里说明找到了目标元素
            prev_node->next = curr_node->next;
            free(curr_node);
            printf("节点%d删除成功！\n", target);
            return true;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    // 走到这里还没有找到就说明，也没有找到
    printf("未找到目标元素%d\n", target);
    return false;
}
