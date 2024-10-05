#include "self_adjusting_arr.h"
#include <stdio.h>

void arr_text(void) {
    SelfAdjustArr arr;
    InitSelfAdjustArr(&arr, 10);

    // 插入一些元素
    InsertToHeaderOfArr(1, &arr);
    InsertToHeaderOfArr(2, &arr);
    InsertToHeaderOfArr(3, &arr);
    InsertToHeaderOfArr(4, &arr);

    // 输出表中元素
    printf("表中元素为：\n");
    for (int i = 0; i < arr.ArrLength; i++)
    {
        int index = (arr.Front + i) % arr.Capacity;
        printf("元素: %d\n", arr.Elements[index]);
    }

    // 查找并将元素移到表头
    Find(3, &arr);

    // 输出表内容以验证
    printf("Find找3之后的表：\n");
    for (int i = 0; i < arr.ArrLength; i++)
    {
        int index = (arr.Front + i) % arr.Capacity;
        printf("元素: %d\n", arr.Elements[index]);
    }

    // 释放内存
    DisposeTheAdjusArr(&arr);
}

int main(void) {
    arr_text();

    return 0;
}