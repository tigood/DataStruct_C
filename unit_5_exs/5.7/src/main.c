/*
在计算的过程中，将两个多项式相乘的结果存储在一个哈希表中，然后将这个哈希表中的内存排序
tips：为了方便实现，这里就固定哈希表的大小了
 */
#include <stdio.h>
#include <stdlib.h>
#define HASHSIZE 101   // 固定哈希表的大小

// 多项式
typedef struct _Term {
	int coeff;  // 系数
	int exp;  // 指数
	struct _Term *next;  // 指向下一个式子的指针
} Term;

// 哈希表
typedef struct _HashTable
{
	Term *table[HASHSIZE];
} HashTable;

// 哈希函数
unsigned int hash(int key) {
	if (key < 0) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return key % HASHSIZE;
}

// 向哈希表中插入一个元素
void insert_elem_hash_table(HashTable *hash_table, int coeff, int exp) {
	// 检测参数合法性
	if (hash_table == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	// 计算位置
	unsigned int index = hash(exp);

	Term *curr_item = hash_table->table[index];
	// 查看该单元是否已经有项
	while (curr_item != NULL) {
		if (curr_item->exp == exp) {
			// 合并系数
			curr_item->coeff += coeff;
			return;
		}
		curr_item = curr_item->next;
	}

	// 如果该单元当前没有元素就创建一个元素插入
	Term *new_term = malloc(sizeof(Term));
	// 初始化新节点
	new_term->coeff = coeff;
	new_term->exp = exp;
	new_term->next = hash_table->table[index];
	hash_table->table[index] = new_term;
}

// 多项式乘法
void term_multiply(HashTable *result, Term *poly1, Term *poly2) {
	// 通过一个双重循环来计算
	for (Term *t1 = poly1; t1 != NULL; t1 = t1->next) {
		for (Term *t2 = poly2; t2 != NULL; t2 = t2->next) {
			// 计算新的幂和系数
			int new_coeff = t1->coeff * t2->coeff;
			int new_exp = t1->exp + t2->exp;
			// 插入哈希表中
			insert_elem_hash_table(result, new_coeff, new_exp);
		}
	}
}

// 排序方法
void sortTerms(Term **terms_arr, int count) {
	// 使用简单的冒泡排序
}

int main(void) {

	return 0;
}