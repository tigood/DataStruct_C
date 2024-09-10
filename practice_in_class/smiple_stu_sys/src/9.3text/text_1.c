#include <stdio.h>
#include <stdbool.h>
#define NUM 2
#define SNOLEN 10
#define SNAMELEN 40
#define CSMAX 5
#define BOUND 60
#define CSNAMELEN 40

const char scores_name[CSMAX][CSNAMELEN] = {"数学", "物理", "英语", "语文", "体育"};

// 定义了一个学生结构体，并顺便定义了一个学生数组
struct Student {
    char sno[SNOLEN]; // 学号
    char sname[SNAMELEN]; // 姓名
    // 成绩  数学 物理 英语 语文 体育
    float scores[CSMAX];
    float average; // 平均成绩
} stu[NUM];

void eat_line();
char *s_gets(char *st, int n);

// 求数学的平均成绩
// 前置条件：传入一个学生结构体数组的首元素指针和学生人数
// 后置条件：计算学生的数学平均成绩并且打印出来
void getMathAver(struct Student *stus, int n);

// 对于有两门以上课程不及格的学生，输出他们的学号 各门成绩及平均成绩
void getBadStu(struct Student *stus, int n);

// 输出成绩优良的学生，所有成绩在80分以上，平均成绩在85分以上学号 各门成绩及平均成绩
void getGoodStu(struct Student *stus, int n);

int main(void)
{
    for (int i = 0; i < NUM; i++) {
        printf("请输入第%d个学生的信息：\n", i + 1);
        printf("请输入学生的学号：");
        s_gets(stu[i].sno, SNOLEN);
        printf("请输入学生的姓名：");
        s_gets(stu[i].sname, SNAMELEN);
        for (int j = 0; j < CSMAX; j++) {
            printf("请输入第%d个学生的%s成绩：", i + 1, scores_name[j]);
            scanf("%f", &stu[i].scores[j]);
            eat_line();
        }
    }
    // 求数学的平均成绩
    getMathAver(stu, NUM);
    // 输出成绩较差的学生
    printf("成绩较差的学生：\n");
    getBadStu(stu, NUM);
    // 输出成绩较好的学生
    printf("成绩较好的学生：\n");
    getGoodStu(stu, NUM);

    return 0;
}

void getMathAver(struct Student *stus, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += stus[i].scores[0];
    }
    printf("本班学生平均成绩为：%.2f\n", sum / n);
    printf("\n");
}

void getBadStu(struct Student* stus, int n) {
    // 通过循环将有不及格成绩的学生筛选出来
    float count; // 计数
    float sum; // 总成绩
    for (int i = 0; i < n; i++)
    {
        count = 0;
        sum = 0;
        // 循环该学生的成绩，计算有几科不及格
        for (int j = 0; j < CSMAX; j++) {
            sum += stus[i].scores[j];
            if (stus[i].scores[j] < BOUND)
                count++;
        }
        if (count >= 2) {
            // 输出该学生的学号成绩
            printf("姓名：%s  学号：%s\n", stus[i].sname, stus[i].sno);
            // 输出该学生的成绩
            for (int k = 0; k < CSMAX; k++) {
                printf("%s成绩为：%.2f\n", scores_name[k], stus[i].scores[k]);
            }
            // 输出平均成绩
            printf("平均成绩为：%.2f\n", sum / CSMAX);
        }
    }
    printf("\n");
}

void getGoodStu(struct Student *stus, int n) {
    bool flag;
    float sum;
    float average;
    
    for (int i = 0; i < n; i++) {
        // 重置数据
        flag = true;
        sum = 0;
        
        // 判断该学生成绩
        for (int j = 0; j < CSMAX; j++) {
            sum += stus[i].scores[j];
            if (stus[i].scores[j] < 80) {
                flag = false;
                break;  // 发现不合格的成绩，跳出循环
            }
        }
        
        // 如果所有成绩都合格，再判断平均成绩
        if (flag) {
            average = sum / CSMAX;
            if (average < 85) {
                flag = false;  // 平均成绩不合格
            }
        }
        
        // 如果符合所有条件，输出学生信息
        if (flag) {
            printf("姓名：%s  学号：%s\n", stus[i].sname, stus[i].sno);
            // 输出学生的各科成绩
            for (int k = 0; k < CSMAX; k++) {
                printf("%s成绩为：%.2f\n", scores_name[k], stus[i].scores[k]);
            }
            // 输出平均成绩
            printf("平均成绩为：%.2f\n", average);
        }
    }
    printf("\n");
}


// 辅助函数
void eat_line() {
    while (getchar() != '\n')
        continue;
}

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
