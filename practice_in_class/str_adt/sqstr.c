#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 字符串类型
typedef struct _SqString {
	char* ch;
	int length;
} SqString;

// 辅助函数
char* s_gets(char* st, int n) {
    char *result_val;
    result_val = fgets(st, n, stdin);
    if (result_val) {
        int i = 0;
        while (result_val[i] != '\n' && result_val[i] != '\0')
            i++;
        // 走到这里说明找到了
        if (result_val[i] == '\n')
            result_val[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return result_val;
}

// 创建字符串
void str_assign(SqString *p_str, char *chars) {
	int i = 0, j = 0;

	while (chars[i] != '\0') {
		i++;
	}

	p_str->ch = malloc(i * sizeof(char));
	if (!p_str->ch) {
		fprintf(stderr, "空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}

	// 初始化
	for (; j < i; j++) {
		p_str->ch[j] = chars[j];
	}
	p_str->length = i;
	printf("字符串创建完毕！\n");
}

void print_str(SqString str) {
	if (!str.length) {
		printf("空串！\n");
		return;
	}

	for (int i = 0; i < str.length; i++)
		printf("%c", str.ch[i]);
	puts("");
}

int bf_index(SqString src_str, SqString target_str, int position) {
	int i = position - 1, j = 0;
	if (position <= 0 || position > src_str.length) {
		printf("参数不合理！\n");
		exit(EXIT_FAILURE); 
	}
	while (i < src_str.length && j < target_str.length) {
		if (src_str.ch[i] == target_str.ch[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	if (j >= target_str.length)
		return i - target_str.length + 1;
	return 0;
}

// 计算 next 数组
void compute_next(SqString pattern, int *next) {
	int j = 0, k = -1;
	next[0] = -1;

	while (j < pattern.length - 1) {
		if (k == -1 || pattern.ch[j] == pattern.ch[k]) {
			++j;
			++k;
			next[j] = k;
		} else {
			k = next[k];
		}
	}
}

// KMP 算法实现
int kmp_index(SqString src_str, SqString target_str, int position) {
	int i = position - 1, j = 0;
	int *next = (int *)malloc(target_str.length * sizeof(int));
	if (!next) {
		fprintf(stderr, "空间开辟失败！\n");
		exit(EXIT_FAILURE);
	}
	compute_next(target_str, next);

	while (i < src_str.length && j < target_str.length) {
		if (j == -1 || src_str.ch[i] == target_str.ch[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
	free(next);

	if (j >= target_str.length)
		return i - target_str.length + 1;
	return 0;
}

int main(void) {
	SqString s, t;
	char str[100];
	printf("请输入目标串：\n");
	s_gets(str, 100);
	str_assign(&s, str);
	printf("请输入目标串：");
	s_gets(str, 100);
	str_assign(&t, str);
	if (bf_index(s, t, 1)) {
		printf("聊天中涉及金融问题，请辨别真伪！\n");
		print_str(s);
	}

	printf("Done!\n");
	return 0;
}