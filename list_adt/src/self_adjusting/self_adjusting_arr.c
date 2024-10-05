#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "self_adjusting_arr.h"

// 判断参数是否为空
void ArgIsNull(SelfAdjustArr *arg) {
    if (arg == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }
}

// 初始化一个自调节表
void InitSelfAdjustArr(SelfAdjustArr *sa_arr, int max_length) {
    // 判断参数
    ArgIsNull(sa_arr);
    // 判断要创建的长度是否
    if (max_length < MIN_LENGTH) {
        fprintf(stderr, "您指定的容量不能小于最小长度\n");
        exit(EXIT_FAILURE);
    }
    sa_arr->Elements = (ElementType *)malloc(sizeof(ElementType) * max_length);
    if (sa_arr->Elements == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
    // 其余参数初始化
    sa_arr->Capacity = max_length;
    sa_arr->ArrLength = 0;
    sa_arr->Front = 0;
    sa_arr->Rear = 0;
}

// 判断自调节表是否已满
bool IsFull(SelfAdjustArr *sa_arr) {
    ArgIsNull(sa_arr);
    return sa_arr->ArrLength == sa_arr->Capacity;
}

// 判断自调节表是否为空
bool IsEmpty(SelfAdjustArr *sa_arr) {
    ArgIsNull(sa_arr);
    return sa_arr->ArrLength == 0;
}

// 将一个自调节表清空
void EmptyTheAdjustArr(SelfAdjustArr *sa_arr) {
    ArgIsNull(sa_arr);
    sa_arr->ArrLength = 0;
    sa_arr->Front = 0;
    sa_arr->Rear = 0;
}

// 释放一个表的例程
void DisposeTheAdjusArr(SelfAdjustArr *sa_arr) {
    ArgIsNull(sa_arr);
    // 释放数组内存
    free(sa_arr->Elements);
    // 由于调节表是占用栈上的内存不是堆上的，所以不能手动释放
}

// 将一个元素插入到自调节表头
bool InsertToHeaderOfArr(ElementType elem, SelfAdjustArr *sa_arr) {
    ArgIsNull(sa_arr);
    if (IsFull(sa_arr)) {
        printf("该表已满，插入失败！\n");
        return false;
    }
    if (IsEmpty(sa_arr)) {
        sa_arr->Elements[sa_arr->Front] = elem;
    } else {
        // 计算出新添加的表头位置
        sa_arr->Front = (sa_arr->Front + sa_arr->Capacity - 1) % sa_arr->Capacity;
        sa_arr->Elements[sa_arr->Front] = elem;
    }
    sa_arr->ArrLength++;
    return true;
}

// 查找元素并将该元素移到表头位置
bool Find(ElementType target, SelfAdjustArr * sa_arr) {
    ArgIsNull(sa_arr);
    // 判断该表是否为空，如果为空就返回
    if (IsEmpty(sa_arr)) {
        printf("该表为空，查找失败！\n");
        return false;
    }
    // 查找目标元素的位置
    int foundIndex = -1;
    int tempIndex;
    for (int i = 0; i < sa_arr->ArrLength; i++) {
        tempIndex = (sa_arr->Front + 1) % sa_arr->Capacity;
        if (sa_arr->Elements[tempIndex] == target) {
            // 走到这里说明找到了
            foundIndex = tempIndex;
            break;  // 退出循环
        }
    }
    if (foundIndex == -1) {
        // 走到这里说明没有找到目标元素
        printf("未找到指定的元素！\n");
        return false;
    }
    // 记录该元素的值
    ElementType tempElem = sa_arr->Elements[foundIndex];

    // 将该元素从源位置删除掉
    int currentIndex = foundIndex;
    while (currentIndex != sa_arr->Front)
    {
        int prevIndex = (currentIndex + sa_arr->Capacity - 1) % sa_arr->Capacity;
        sa_arr->Elements[currentIndex] = sa_arr->Elements[prevIndex];
        currentIndex = prevIndex;
    }
    // 将目标元素放到表头位置
    sa_arr->Elements[sa_arr->Front] = tempElem;

    printf("元素插入成功！\n");
    return true;
}