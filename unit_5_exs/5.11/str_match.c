#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLESIZE 107

// 简单的加法哈希函数
unsigned int hash(const char *key, int len) {
    unsigned int hash_val = 0;
    for (int i = 0; i < len; i++) {
        hash_val += key[i];
    }
    return hash_val % TABLESIZE;
}

// 计算滚动哈希
unsigned int roll_hash(unsigned int hash_val, char old_char, char new_char, int table_size) {
    // 移除旧字符的贡献并添加新字符的贡献
    hash_val = (hash_val - old_char + new_char) % table_size;
    return hash_val;
}

// 计算子串在父串中第一次出现的位置
int str_match(char *str_1, char *str_2) {
    int str_1_len = strlen(str_1);
    int str_2_len = strlen(str_2);
    
    if (str_1_len < str_2_len) {
        printf("父串的长度太小，子串肯定不存在！\n");
        return -1;
    }

    // 计算目标子串的哈希值
    unsigned int str_2_hash = hash(str_2, str_2_len);

    // 计算父串的第一个子串的哈希值
    unsigned int hash_val = hash(str_1, str_2_len);

    // 如果第一个子串的哈希值与目标子串相等，进行字符逐个比较
    if (hash_val == str_2_hash) {
        bool flag = true;
        for (int i = 0; i < str_2_len; i++) {
            if (str_1[i] != str_2[i]) {
                flag = false;
                break;
            }
        }
        if (flag) return 0;  // 找到匹配
    }

    // 滚动哈希处理其余子串
    for (int i = 1; i <= str_1_len - str_2_len; i++) {
        // 更新哈希值
        hash_val = roll_hash(hash_val, str_1[i - 1], str_1[i + str_2_len - 1], TABLESIZE);

        // 如果哈希值匹配，则逐个字符检查
        if (hash_val == str_2_hash) {
            bool flag = true;
            for (int j = 0; j < str_2_len; j++) {
                if (str_1[i + j] != str_2[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return i;  // 找到匹配
        }
    }

    return -1;  // 没有找到匹配的子串
}

int main(void) {
    char *str1 = "hello";
    char *str2 = "ll";
    int pos = str_match(str1, str2);
    printf("匹配的索引位置: %d\n", pos);  // 应该输出2，表示子串 "ll" 从父串 "hello" 的索引 2 开始
    return 0;
}
