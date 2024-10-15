#include <stdio.h>
#include <stdlib.h>

struct Node;

typedef int ElementType;
typedef struct Node Monkey;
typedef struct Node *CMonkeyList;

struct Node {
    ElementType elem;
    Monkey *next;
};

// 创建猴圈
CMonkeyList make_monkeys_list(int n) {
    // 创建不带头节点的循环链表的头指针
    CMonkeyList head;
    Monkey *curr, *rear;  // 指向当前节点的指针和尾节点的指针
    // 创建第一个节点
    head = (Monkey *)malloc(sizeof(struct Node));
    if (head == NULL) {
        // 空间开辟失败
        fprintf(stderr, "空间开辟失败！\n");
        return NULL;
    }
    // 初始化头节点
    head->elem = 1;
    head->next = head;
    rear = head;

    // 创建剩下的节点
    for (int i = 2; i <= n; i++) {
        // 创建节点
        curr = (Monkey *)malloc(sizeof(struct Node));
        if (!curr) {
            fprintf(stderr, "空间开辟失败！\n");
            return NULL;
        }
        // 初始化节点
        curr->elem = i;
        curr->next = rear->next;
        rear->next = curr;
        // 移动尾节点
        rear = curr;
    }
    printf("猴圈创建成功！\n");
    return head;
}

// 打印循环链表
void printf_monkeys_list(CMonkeyList list) {
    if (list == NULL) {
        fprintf(stderr, "猴圈为空打印失败！\n");
        return;
    }
    Monkey *curr = list;
    while (curr->next != list)
    {
        printf("%d  ", curr->elem);
        curr = curr->next;
    }
    // 打印最后一个
    printf("%d  ", curr->elem);
    printf("\n");
}

void find_monkey_king(CMonkeyList list, int n) {
    Monkey *curr, *prev;  // 当前猴子和猴子前驱
    curr = list;
    int i = 1;
    while (list->next != list) {
        printf("say: 编号为%d的那只猴子报%d\n", curr->elem, i);
        if (i == n - 1){
            // 记录前驱
            prev = curr;
            curr = curr->next;
        }
        else if (i == n)
        {
            printf("del: 编号为%d的猴子被删掉了！\n", curr->elem);
            prev->next = curr->next;
            // 如果当前节点为头指针，则更新
            if (curr == list) {
                list = curr->next;
            }
            free(curr);
            curr = prev->next;
            // 重置计数器
            i = 0;
            printf("info: 剩余猴子：");
            printf_monkeys_list(list);
        }
        else
        {
            // 向前移动
            curr = curr->next;
        }
        i++;  // 叠加报号
    }

    // 猴子王为
    printf("result: 猴子king的编号为：%d\n", list->elem);
}

int main(void) {
    int counts, cycles_num;
    printf("请输入有几个猴子：\n");
    scanf("%d", &counts);
    printf("请输入报到那个号码的要被删除：");
    scanf("%d", &cycles_num);
    CMonkeyList list = make_monkeys_list(counts);
    printf_monkeys_list(list);
    printf("开始找猴王：\n");
    if (cycles_num == 1) {
        printf("猴王为：%d\n", counts);
    } else {
        find_monkey_king(list, cycles_num);
    }

    return 0;
}
