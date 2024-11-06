#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATEMENTS 1000  // 假设语句条数最多为1000

// 结构体表示每条语句
typedef struct {
    int line_number;   // 语句编号
    char statement[1000];  // 语句内容
} Statement;

// 读入输入并处理
int main() {
    int N, F, D;
    Statement statements[MAX_STATEMENTS];

    // 输入语句数量，起始语句编号，编号增量
    scanf("%d %d %d", &N, &F, &D);
    
    // 读入每条语句
    for (int i = 0; i < N; i++) {
        scanf("%d", &statements[i].line_number);  // 读取语句编号
        getchar();  // 读取语句编号后的换行符，跳过该换行符
        fgets(statements[i].statement, sizeof(statements[i].statement), stdin);  // 读取语句内容

        // 移除末尾的换行符（如果有的话）
        size_t len = strlen(statements[i].statement);
        if (len > 0 && statements[i].statement[len - 1] == '\n') {
            statements[i].statement[len - 1] = '\0';
        }
    }

    // 输出修改后的语句
    for (int i = 0; i < N; i++) {
        // 重新编号
        int new_line_number = F + i * D;
        printf("%d %s\n", new_line_number, statements[i].statement);
    }

    return 0;
}
