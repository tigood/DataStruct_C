#include "self_adjusting_list.h"
#include <stdio.h>

void list_text(void) {
    SelfAdjustList sa_list;
    InitSelfAdjustList(&sa_list);
    InsertToHeaderOfList(1, sa_list);
    InsertToHeaderOfList(2, sa_list);
    InsertToHeaderOfList(3, sa_list);
    InsertToHeaderOfList(4, sa_list);

    printf("当前的表头元素为：\n");
    printf("%d\n", Front(sa_list));
    
    // 进行find操作
    Find(3, sa_list);

    printf("现在的表头元素为：\n");
    printf("%d\n", Front(sa_list));

    DisposeTheAdjusList(sa_list);
}

int main(void) {
    list_text();

    return 0;
}