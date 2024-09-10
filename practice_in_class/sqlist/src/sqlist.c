#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 20
#define INCREMENT 10

typedef int ElemType;
// 顺序表结构
typedef struct {
    ElemType *elem;
    int length;  // 顺序表当前的长度
    int listsize;  // 顺序表的容量
}SqList;

// 判断顺序表是否为空
bool ListEmpty(const SqList *pL);

// 销毁一个顺序表
void DestroyList(SqList *pL);

// 初始化一个顺序表
SqList InitList();

// 通过键盘输入数据创建一个顺序表
SqList CreateList(int n);

// 打印顺序表
void PrintList(const SqList *pL);

// 在顺序表中插入元素
bool InsertList(SqList *pL, int i, ElemType e);

// 在顺序表中的删除指定位置的元素
bool ListDelete(SqList *pL, int i, ElemType *e);

// 在顺序表中定位一个元素
int LocaleElem(const SqList *pL, ElemType e);

// 在顺序表中根据位置读取一个元素
bool GetElem(const SqList *pL, int i, ElemType *e);

// 顺序表表长
int ListLength(const SqList *pL);

// 合并顺序表
bool Combine(const SqList L1, const SqList L2, SqList *targetList);

// 展示选项
int showMenu();

int main() {
    SqList L, L1, L2, L3;
    int n, index, elem;
    ElemType e;
    int choose;
    do
    {
        choose = showMenu();
        // 执行操作
        switch (choose)
        {
        case 1:
            printf("请输入您要创建一个内含多少个元素的表：");
            scanf("%d", &n);
            if (n < 0 || n > MAXSIZE) {
                printf("输入数值不正确，请在合理初始化范围内输入！\n");
            } else {
                L = CreateList(n);
                PrintList(&L);
            }
            break;
        case 2:
            if (ListEmpty(&L)) {
                printf("该列表为空！\n");
            } else {
                printf("该列表不为空！\n");
            }
            break;
        case 3:
            printf("该顺序表的长度为：%d\n", ListLength(&L));
            break;
        case 4:
            printf("请输入您要查看的位置：\n");
            scanf("%d", &n);
            GetElem(&L, n, &e);
            printf("第%d个元素的值为：%d\n", n, e);
            break;
        case 5:
            int target;
            printf("请输入您要查找的元素，我们将返回你他的位置\n");
            scanf("%d", &target);
            index = LocaleElem(&L, target);
            printf("%d在是顺序表的第%d个值\n", target, index);
            break;
        case 6:
            printf("请输入您要插入的元素：");
            scanf("%d", &elem);
            printf("请输入您要插入的位置：");
            scanf("%d", &index);
            if (InsertList(&L, index, elem)) {
                printf("插入成功！\n");
            } else {
                printf("插入失败！\n");
            }
            break;
        case 7:
            printf("请你输入您要删除的元素的位置：");
            scanf("%d", &index);
            if (ListDelete(&L, index, &elem)) {
                printf("删除成功！\n");
                printf("您删除的元素为：%d\n", elem);
            }
            else
            {
                printf("删除失败！\n");
            }
            break;
        case 8:
            printf("请构造两个顺序表，元素为非递减序列！\n");
            printf("请构造L1， 元素为非递减序列！\n");
            printf("请输入La的元素个数\n");
            scanf("%d", &n);
            L1 = CreateList(n);
            if (L1.length) {
                PrintList(&L1);
            }
            printf("请构造L2，元素为非递减序列！\n");
            printf("请输入L2的元素个数:\n");
            scanf("%d", &n);
            L2 = CreateList(n);
            if (L2.length) {
                PrintList(&L2);
            }
            // 合并
            Combine(L1, L2, &L3);
            printf("合并之后：\n");
            PrintList(&L3);

            break;
        case 0:
            printf("退出！\n");
            break;

        default:
            printf("请输入合理的选项：(0-8)\n");
            break;
        }
    } while (choose);

    return 0;
}

bool ListEmpty(const SqList *pL) {
    if (pL->length == 0)
        return true;
    return false;
}

void DestroyList(SqList *pL) {
    // 释放指向的空间
    free(pL->elem);
    // 重置数据
    pL->elem = NULL;
    pL->length = 0;
    pL->listsize = 0;
}

SqList InitList() {
    SqList L;
    L.elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if (!L.elem) {
        fprintf(stderr, "空间开辟失败\n");
        exit(EXIT_FAILURE);
    }
    L.length = 0;
    L.listsize = MAXSIZE;
    // 将初始化好了的顺序表返回
    return L;
}

SqList CreateList(int n) {
    // 初始化一个顺序表
    SqList L = InitList();
    printf("请输入一个顺序表：\n");
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个元素\n", i + 1);
        scanf("%d", &L.elem[i]);
    }
    // 修改顺序表长度
    L.length = n;
    return L;
}

void PrintList(const SqList *pL) {
    if (pL->length == 0) {
        printf("这是一个空的顺序表！\n");
        return;
    }
    printf("顺序表内容如下：\n");
    for (int i = 0; i < pL->length; i++) {
        printf("%d  ", pL->elem[i]);
    }
    printf("\n");
}

bool InsertList(SqList *pL, int i, ElemType e) {
    // 这里的i代表的是位置并不是下标
    if (i < 1 || i > pL->length + 1) {
        printf("插入位置不合理\n");
        return false;
    }
    // 判断是否还有存储空间
    if (pL->length >= pL->listsize) {
        // 增加部分空间
        ElemType* newbase = (ElemType *)realloc(pL->elem, (pL->listsize + INCREMENT) * sizeof(ElemType));
        if (!newbase) {
            fprintf(stderr, "空间分配失败\n");
            exit(EXIT_FAILURE);
        }
        pL->elem = newbase;
        pL->listsize += INCREMENT;
    }
    // 将数组部分元素移动，腾出空间
    for (int j = pL->length - 1; j >= i - 1; j--) {
        pL->elem[j + 1] = pL->elem[j];
    }
    // 将新元素插入
    pL->elem[i - 1] = e;
    pL->length++;
    return true;
}

bool ListDelete(SqList *pL, int i, ElemType *e) {
    // 这个i也是指的位置，不是下标
    if (i < 1 || i > pL->length) {
        fprintf(stderr, "删除的位置不合理");
        exit(EXIT_FAILURE);
    }
    // 将被删除的元素传出
    *e = pL->elem[i - 1];
    // 移动元素覆盖值
    for (int j = i; j <= pL->length;  j++)
    {
        pL->elem[i - 1] = pL->elem[i];
    }
    // 递减数组容量
    pL->length--;
    return true;
}

int LocaleElem(const SqList *pL, ElemType e) {
    // 定位一个元素 返回的是一个位置
    for (int i = 0; i < pL->length; i++) {
        if (pL->elem[i] == e)
            return i + 1;
    }
    return -1;
}

bool GetElem(const SqList *pL, int i, ElemType *e) {
    // 通过位置读取元素
    if (i < 1 || i > pL->length) {
        fprintf(stderr, "输入的位置不合理！\n");
        return false;
    }
    *e = pL->elem[i - 1];
    return true;
}

int ListLength(const SqList *pL) {
    return pL->length;
}

bool Combine(const SqList L1, const SqList L2, SqList *targetList) {
    // 设置目标顺序表的空间
    targetList->listsize = targetList->length = L1.length + L2.length;
    
    // // 释放之前的空间
    // free(targetList->elem);
    
    // 重新分配空间
    targetList->elem = (ElemType *)malloc(sizeof(ElemType) * targetList->listsize);
    if (!targetList->elem) {
        fprintf(stderr, "空间开辟失败！\n");
        return false;
    }
    // 使用归并合并
    ElemType* tempL1_p = L1.elem;
    ElemType* tempL2_p = L2.elem;
    ElemType* L1_end = L1.elem + L1.length - 1;
    ElemType* L2_end = L2.elem + L2.length - 1;

    // 创建临时指针来操作 targetList
    ElemType* tempTarget_p = targetList->elem;

    while (tempL1_p <= L1_end && tempL2_p <= L2_end) {
        if (*tempL1_p < *tempL2_p) {
            *tempTarget_p++ = *tempL1_p++;
        } else {
            *tempTarget_p++ = *tempL2_p++;
        }
    }
    // 将剩下的元素复制到 targetList
    while (tempL1_p <= L1_end) {
        *tempTarget_p++ = *tempL1_p++;
    }

    while (tempL2_p <= L2_end) {
        *tempTarget_p++ = *tempL2_p++;
    }

    return true;
}

int showMenu() {
    int choose;
    printf("----------------- 顺序表运算 ------------------\n");
    printf("----------------- 1.   建表 ------------------\n");
    printf("----------------- 2.   判空 ------------------\n");
    printf("----------------- 3.  求表长 ------------------\n");
    printf("----------------- 4.按位置查找 ------------------\n");
    printf("----------------- 5.按数值查找 ------------------\n");
    printf("----------------- 6.   插入 ------------------\n");
    printf("----------------- 7.   删除 ------------------\n");
    printf("----------------- 8.   合并 ------------------\n");
    printf("----------------- 0.   退出 ------------------\n");
    scanf("%d", &choose);
    return choose;
}
