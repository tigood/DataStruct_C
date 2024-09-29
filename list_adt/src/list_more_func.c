#include "list.h"
#include "list_more_func.h"
#include <stdio.h>

List ListsUnion(const List list_1, const List list_2) {
    ptrToNode list_1_start = list_1->next;
    ptrToNode list_2_start = list_2->next;
    List result;
    initList(&result);
    // 记录结果列表的尾节点
    ptrToNode result_last = result;
    while (list_1_start != NULL && list_2_start != NULL) {
        if (list_1_start->element < list_2_start->element) {
            // 查找小的这一方是否已经存在了
            // 如果没有存在的话，就将它加入
            if (find(list_1_start->element, &result) == NULL) {
                // 将该元素插入新列表
                insertItem(list_1_start->element, &result, result_last);
                // 更新尾节点
                result_last = result_last->next;
            }
            // 移动小的这一方
            list_1_start = list_1_start->next;
        } else if (list_1_start->element > list_2_start->element) {
            if (find(list_2_start->element, &result) == NULL) {
                // 将元素插入
                insertItem(list_2_start->element, &result, result_last);
                // 更新尾节点
                result_last = result_last->next;
            }
            list_2_start = list_2_start->next;
        } else {
            // 元素相等的情况，只需要将其中一个加入就可以
            if (find(list_1_start->element, &result) == NULL) {
                insertItem(list_1_start->element, &result, result_last);
                // 更新尾节点
                result_last = result_last->next;
            }
            list_1_start = list_1_start->next;
            list_2_start = list_2_start->next;
        }
    }
    // 将两个链表中的剩余的适合元素加入结果集中
    while (list_1_start != NULL) {
        if (find(list_1_start->element, &result) == NULL) {
            insertItem(list_1_start->element, &result, result_last);
            result_last = result_last->next;
        }
        list_1_start = list_1_start->next;
    }

    while (list_2_start != NULL) {
        if (find(list_2_start->element, &result) == NULL) {
            insertItem(list_2_start->element, &result, result_last);
            result_last = result_last->next;
        }
        list_2_start = list_2_start->next;
    }

    return result;
}

List ListsIntersect(const List list_1, const List list_2) {
    ptrToNode list_1_temp = list_1->next;
    ptrToNode list_2_temp = list_2->next;
    List result;
    initList(&result);
    ptrToNode result_last = result;
    while (list_1_temp != NULL && list_2_temp != NULL) {
        if (list_1_temp->element < list_2_temp->element) {
            list_1_temp = list_1_temp->next;
        } else if (list_1_temp->element > list_2_temp->element) {
            list_2_temp = list_2_temp->next;
        } else {
            if (find(list_1_temp->element, &result) == NULL) {
                insertItem(list_1_temp->element, &result, result_last);
                result_last = result_last->next;
            }
            list_1_temp = list_1_temp->next;
            list_2_temp = list_2_temp->next;
        }
    }

    return result;
}