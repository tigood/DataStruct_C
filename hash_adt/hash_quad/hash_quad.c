//
// Created by tigood on 2024/11/2.
// 这是一个使用平方探测法实现的散列
//
#include "hash_quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

// 创建一个哈希表
HashTable create_hash_table_quad(int table_size) {
    // 检测参数合法性
    if (table_size < MINCAL) {
        fprintf(stderr, "创建的哈希表的长度太短！\n");
        exit(EXIT_FAILURE);
    }

    // 开辟一个哈希表的空间
    HashTable hash_table = malloc(sizeof(HashTable));
    if (!hash_table) {
        fprintf(stderr, "哈希表空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 初始化哈希表
    hash_table->table_size = next_prime(table_size);
    // 为哈希表的单元们开辟空间
    hash_table->table = malloc(hash_table->table_size * sizeof(Cell));
    if (!hash_table->table) {
        fprintf(stderr, "哈希表空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 为每一个单元初始化
    for (int i = 0; i < hash_table->table_size; i++) {
        hash_table->table[i].info = Empty;
    }

    return hash_table;
}

// 销毁一个哈希表
void destroy_hash_table_quad(HashTable *p_hash_table) {
    if (*p_hash_table == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    if (!(*p_hash_table)->table) {
        free((*p_hash_table)->table);
    }
    free(*p_hash_table);
    // 重置指针
    *p_hash_table = NULL;
}

// 根据值找到目标节点
Position find_elem_hash_table_quad(HashTable hash_table, ElementType elem) {
    // 参数合法性检测
    if (hash_table == NULL) {
        fprintf(stderr, "参数合法性检测失败！\n");
        exit(EXIT_FAILURE);
    }

    Position curr_pos;  // 记录当前的位置
    int collision_num = 0;  // 探测次数
    // 计算起始位置
    curr_pos = hash(elem, hash_table->table_size);
    while (hash_table->table[curr_pos].info != Empty && hash_table->table[curr_pos].elem != elem) {
        // 这里假设散列表的大小至少为表中元素个数的二倍，不然这里就要加入额外的判断了
        // 这是原书中的代码，但是我觉得这并不是标准意义的平方探测
        // curr_pos = 2 * ++collision_num - 1;  // 实际上是使用的二进制移位
        // if (curr_pos >= hash_table->table_size) {
        //     curr_pos = curr_pos - hash_table->table_size;
        // }
        collision_num++;
        curr_pos = (curr_pos + collision_num * collision_num) % hash_table->table_size;
    }

    return curr_pos;
}

// 向指定的哈希表中插入一个指定元素
void insert_elem_hash_table_quad(HashTable hash_table, ElementType elem) {
    if (!hash_table) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    // 查看元素是否在表中
    Position target_pos = find_elem_hash_table_quad(hash_table, elem);
    if (hash_table->table[target_pos].info != Legitimate) {
        hash_table->table[target_pos].info = Legitimate;
        hash_table->table[target_pos].elem = elem;
        printf("%d插入成功！\n", elem);
    }
}

// 取出哈希表单元格中的值
ElementType retrieve_elem_hash_table_quad(HashTable hash_table, Position pos) {
    if (!hash_table) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    if (hash_table->table[pos].info == Legitimate) {
        return hash_table->table[pos].elem;
    } else {
        fprintf(stderr, "该位置为空！\n");
        exit(EXIT_FAILURE);
    }
}

// 向指定的哈希表删除一个指定的元素
void delete_elem_hash_table_quad(HashTable hash_table, ElementType elem) {
    if (!hash_table) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    Position target_pos = find_elem_hash_table_quad(hash_table, elem);
    if (hash_table->table[target_pos].info == Legitimate) {
        hash_table->table[target_pos].info = Deleted;
        printf("%d删除成功！\n", elem);
    } else {
        // 走到这里说明这个没有元素或者该元素已经被懒惰删除
        fprintf(stderr, "指定删除的元素不存在");
        exit(EXIT_FAILURE);
    }
}

// 再散列
HashTable rehash_hash_table_quad(HashTable hash_table) {
    // 参数合法性检测
    if (!hash_table) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }

    int old_table_size = hash_table->table_size;
    HashTable old_hash_table = hash_table;

    // 创建一个双倍大小的新表
    hash_table = create_hash_table_quad(next_prime(2 * old_table_size));

    for (int i = 0; i < old_table_size; i++) {
        if (old_hash_table->table[i].info == Legitimate) {
            insert_elem_hash_table_quad(hash_table, old_hash_table->table[i].elem);
        }
    }

    // 释放原来的空间
    destroy_hash_table_quad(&old_hash_table);

    return hash_table;
}
