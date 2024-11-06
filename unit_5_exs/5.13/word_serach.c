/*
字谜程序，使用散列表算法实现
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TABLESIZE 107  // 哈希表大小
#define COLS 4   // 字符数组的列数
#define ROWS 4   // 字符数组的行数

/*
哈希表实现部分
 */

// 哈希表中的每一个节点
typedef struct _Node {
	char *word;   // 当前位置存储的单词
	struct _Node *next;  // 指向下一个元素的指针
} Node;

// 哈希表
typedef struct _HashTable {
	Node *tables[TABLESIZE];
} HashTable;

// 哈希函数
unsigned int hash(const char *key) {
	unsigned int hash_val = 0;

	while (*key != '\0')
		hash_val += (hash_val << 5) + *key++;

	return hash_val % TABLESIZE;
}

// 创建一个哈希表
HashTable* init_hash_table(void) {
	// 开辟一个哈希表的空间
	HashTable *hash_table = malloc(sizeof(HashTable));
	if (!hash_table) {
		fprintf(stderr, "哈希表空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}
	// 为里面的单元开辟空间
	memset(hash_table->tables, 0, sizeof(hash_table->tables));  // 将每一个单元的值初始化为0

	printf("哈希表创建成功！\n");
	return hash_table;
}

// 插入一个元素
bool insert_elem_hash_table(HashTable *hash_table, const char *word) {
	// 计算目标位置
	unsigned int index = hash(word);

	// 创建一个新节点
	Node *new_node = malloc(sizeof(Node));
	if (!new_node) {
		fprintf(stderr, "节点空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}
	// 初始化节点并插入
	new_node->word = strdup(word);
	new_node->next = hash_table->tables[index];
	hash_table->tables[index] = new_node;
	printf("元素%s插入成功！\n", word);

	return hash_table;
}

// 查找单词是否在哈希表中
bool search_for_hash_table(HashTable *hash_table, const char* word) {
	// 计算单词的哈希值
	unsigned int index = hash(word);
	Node *curr = hash_table->tables[index];
	while (curr) {
		if (strcmp(curr->word, word) == 0) {
			// 如果目标值与当前值一致
			return true;
		}
		curr = curr->next;
	}

	return false;
}

// 释放哈希表内存
void destory_hash_table(HashTable *hash_table) {
	if (!hash_table) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	// 释放每一个单元格的空间
	for (int i = 0; i < TABLESIZE; i++) {
		Node *curr = hash_table->tables[i];
		while (curr) {
			Node *temp = curr;
			curr = curr->next;
			// 释放空间
			free(temp->word);  // 由于这里的word是通过strdup复制开辟的，需要手动释放
			free(temp);
		}
	}

	// 释放哈希表的内存
	free(hash_table);
}

/*
算法实现部分
 */

// 定义八个方向
int directions[8][2] = {  // row, col
	{1, 0},   // 下
	{0, 1},   // 右
	{-1, 0},  // 上
	{0, -1},   // 左
	{1, 1},   // 右下
	{1, -1},  // 左下
	{-1, 1},  // 右上
	{-1, -1}  // 左上
};

// 递归字符检测单词
// board   二维数组，代表字符表
// row     代表当前字符在二维数组中的行坐标
// col     代表当前字符在二维数组中的列坐标
// word    代表目标单词
// index   代表正在比对到目标单词的第几个子母了
// direction 代表当前检测的方向
bool search_word_recu(char board[ROWS][COLS], int row, int col, const char* word, int index, int direction[2]) {
	if (word[index] == '\0')
		// 走到这里代表当前单词已经检测完毕了
		return true;

	// 检测当前位置是否仍然在矩阵中
	if (row < 0 || col < 0 || row >= ROWS || col >= COLS) 
		return false;

	// 当前字符检测失败，返回false
	if (board[row][col] != word[index])
		return false;

	// 递归查找下一个字符
	printf("当前字符%c比对成功！\n", word[index]);
	return search_word_recu(board, row + direction[0], col + direction[1], word, index + 1, direction);
}

// 判断一个单词是否在矩阵中
bool word_exits(char board[ROWS][COLS], HashTable *hash_table, const char* word) {
	if (!search_for_hash_table(hash_table, word)) {
		printf("目标单词不存在字典中！\n");
		return false;
	}

	// 遍历字符表中每一个字符，进行查询
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			for (int k = 0; k < 8; k++) {
				if (search_word_recu(board, i, j, word, 0, directions[k])) {
					return true;
				}
			}
		}
	}

	return false;
}

int main(void) {

	char board[ROWS][COLS] = {
		{'t', 'h', 'i', 's'},
		{'w', 'a', 't', 's'},
		{'o', 'a', 'h', 'g'},
		{'f', 'g', 'd', 't'}
	};

	const char *words[] = {"this", "two", "fat", "that", "hello"};

	HashTable *hash_table = init_hash_table();
	for (int i = 0; i < 5; i++) {
		insert_elem_hash_table(hash_table, words[i]);
	}

	if (word_exits(board, hash_table, "this")) {
		printf("this单词存在!\n");
	} else {
		printf("this不存在！\n");
	}

	if (word_exits(board, hash_table, "that")) {
		printf("that单词存在!\n");
	} else {
		printf("that不存在！\n");
	}

	if (word_exits(board, hash_table, "hello")) {
		printf("hello单词存在!\n");
	} else {
		printf("hello不存在！\n");
	}

	return 0;
}