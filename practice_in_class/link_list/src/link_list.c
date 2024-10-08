#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "link_list.h"

// 参数合法性检测
void arg_is_null(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "参数传递不合法！\n");
        exit(EXIT_FAILURE);
    }
}

// 检测空间是否正常开辟
void check_malloc(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }
}

// 以返回值的形式初始化一个链表
LinkList init_list_return(void) {
    // 为头节点开辟空间
    LinkList list = (ptrToNode)malloc(sizeof(struct Node));

    // 判断是否开辟成功
    if (!list) {
        fprintf(stderr, "头节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化头节点
    list->next = NULL;

    return list;
}

// 以指针的形式初始化一个链表
void init_list(LinkList *p_list) {
    // 参数合法性检测
    arg_is_null(p_list);

    // 尾头节点开辟空间
    (*p_list) = (ptrToNode)malloc(sizeof(struct Node));

    // 判断空间是否开辟成功
    check_malloc(*p_list);

    // 初始化头节点
    (*p_list)->next = NULL;
}

// 创建单链表，批量插入并链接一批节点。头插法
bool create_list_front(LinkList list, int n) {
    // 检测参数合法性
    arg_is_null(list);
    if (n <= 0) {
        printf("节点数量过少！\n");
        return false;
    }

    // 通过循环添加元素
    for (int i = 0; i < n; i++) {
        // 开辟新节点
        ptrToNode new_node = (ptrToNode)malloc(sizeof(struct Node));

        // 判断新节点是否开辟成功
        check_malloc(new_node);

        // 节点开辟成功初始化节点
        printf("请输入第%d个元素的值：", i + 1);
        scanf("%d", &new_node->elem);
        new_node->next = list->next;
        list->next = new_node;
    }

    return true;
}

// 创建单链表，批量插入一组节点。尾插法
bool create_list_rear(LinkList list, int n) {
    // 检测参数合法性
    arg_is_null(list);
    if (n <= 0) {
        printf("节点数量过少！\n");
        return false;
    }

    // 通过循环创建节点 
    // 指向尾节点的指针
    ptrToNode rear = list;
    for (int i = 0; i < n; i++) {
        // 为新节点开辟空间
        ptrToNode new_node = (ptrToNode)malloc(sizeof(struct Node));

        // 检测空间是否开辟成功
        check_malloc(new_node);

        // 初始化节点
        printf("请输入第%d个元素的值：", i + 1);
        scanf("%d", &new_node->elem);
        new_node->next = NULL;
        rear->next = new_node;
        rear = new_node;
    }

    return true;
}

// 创建单链表，随机生成一组数组插入链表，使用尾插法
bool create_list_rear_random(LinkList list, int n) {
    // 检测参数合法性
    arg_is_null(list);
    if (n <= 0) {
        printf("节点数量过少！\n");
        return false;
    }

    // 随机种子
    srand(time(0));

    // 通过循环创建节点 
    // 指向尾节点的指针
    ptrToNode rear = list;
    for (int i = 0; i < n; i++) {
        // 为新节点开辟空间
        ptrToNode new_node = (ptrToNode)malloc(sizeof(struct Node));

        // 检测空间是否开辟成功
        check_malloc(new_node);

        // 初始化节点
        // 使用随机数填充链表
        new_node->elem = rand() % 100 + 1; // [1, 100]
        new_node->next = NULL;
        rear->next = new_node;
        rear = new_node;
    }

    return true;
}

// 判断链表是否为空
bool is_empty(LinkList list) {
    // 检测参数合法性
    arg_is_null(list);

    return list->next == NULL;
}

// 打印单链表
bool print_list(LinkList list) {
    // 检测参数合法性
    arg_is_null(list);

    // 判断链表是否为空
    if (is_empty(list)) {
        printf("链表为空！打印失败！\n");
        return false;
    }

    // 走到这里说明不为空
    ptrToNode curr = list->next;
    while (curr != NULL) {
        printf("%d ", curr->elem);
        curr = curr->next;
    }
    printf("\n");

    return true;
}

// 单链表位置查找，按位置查找
bool get_elem_by_position(LinkList list, int position, ElementType *result) {
    // 检测参数合法性
    arg_is_null(list);
    if (position < 1) {
        printf("查找位置不合理！\n");
        return false;
    }

    // 遍历链表查找
    ptrToNode curr = list->next;
    int curr_position = 1;
    while (curr_position < position && curr != NULL)
    {
        curr = curr->next;
        curr_position++;
    }

    // 判断是否找到了目标元素
    if (!curr) {
        // 如果走到这里就说明没有找到目标元素
        printf("没有找到目标元素！\n");
        return false;
    }

    // 找到了目标元素
    *result = curr->elem;
    return true;
}

// 根据元素值在单链表中查找元素
int find_node_by_value(LinkList list, ElementType target) {
    // 检测参数合法性
    arg_is_null(list);

    // 遍历链表查找位置
    ptrToNode curr = list->next;
    int curr_position = 1;
    while (curr != NULL) {
        if (curr->elem == target)
            break;
        curr = curr->next;
        curr_position++;
    }

    // 判断是否找到了
    if (!curr) {
        // 走到这里说明没有找到
        printf("指定元素%d没有在链表中！\n", target);
        return -1;
    }

    return curr_position;
}

// 将指定元素插入到指定位置元素的前面
bool insert_node_by_position(LinkList list, int position, ElementType elem) {
    // 检测参数合法性
    arg_is_null(list);
    if (position < 1) {
        printf("指定的位置不合理！\n");
        return false;
    }

    // 通过循环找到目标位置
    ptrToNode curr = list->next;
    ptrToNode prev = list;
    int curr_position = 1;
    while (curr_position < position && curr != NULL) {
        prev = curr;
        curr = curr->next;
        curr_position++;
    }

    // 判断是否找到了指定位置
    if(!curr) {
        // 走到这里说明没有找到
        printf("指定的位置不合理！\n");
        return false;
    }

    // 走到这里说明找到了
    // 创建新节点
    ptrToNode new_node = (ptrToNode)malloc(sizeof(struct Node));

    // 判断新节点是否开辟成功
    check_malloc(new_node);

    // 初始化节点并插入
    new_node->elem = elem;
    new_node->next = curr;
    prev->next = new_node;

    return true;
}

// 按位置删除元素
bool delete_node_by_position(LinkList list, int position, ElementType *deleted_elem) {
    // 检测参数合法性
    arg_is_null(list);
    if (position < 1) {
        printf("传入位置不合理！\n");
        return false;
    }

    // 通过循环找到目标位置
    ptrToNode curr = list->next;
    ptrToNode prev = list;
    int curr_position = 1;
    while (curr_position < position && curr != NULL) {
        prev = curr;
        curr = curr->next;
        curr_position++;
    }

    // 判断是否找到元素
    if (!curr) {
        // 走到这里说明没有找到
        printf("传入位置不合理！\n");
        return false;
    }

    // 删除当前元素
    *deleted_elem = curr->elem;
    prev->next = curr->next;
    // 释放空间
    free(curr);

    return true;
}

// 按数值删除元素，删除找到的第一个元素
bool delete_node_by_value(LinkList list, ElementType target) {
    // 检测参数合法性
    arg_is_null(list);

    // 通过循环查找目标元素
    ptrToNode curr = list->next;
    ptrToNode prev = list;
    while (curr != NULL) {
        if (curr->elem == target)
            break;
        prev = curr;
        curr = curr->next;
    }

    // 判断是否找到了元素
    if (!curr) {
        // 走到这里说明没有找到元素
        printf("未找到指定元素%d\n", target);
        return false;
    }

    // 删除元素
    prev->next = curr->next;
    free(curr);

    return true;
}

// 按数值删除，删除链表中所有与指定数值相等的元素
bool delete_nodes_by_value(LinkList list, ElementType target) {
    // 参数合法性检测
    arg_is_null(list);

    // 设置标志
    bool is_found = false;

    // 通过循环逐一删除
    ptrToNode curr = list->next;
    ptrToNode prev = list;
    while (curr != NULL) {
        if (curr->elem == target) {
            // 走到这里说明找到了一个目标元素
            if (!is_found) {
                // 修改标志
                is_found = true;
            }
            // 删除当前节点
            ptrToNode temp = curr;
            prev->next = curr->next;
            curr = prev->next;
            // 释放节点
            free(temp);
        } else {
            // 说明当前不是目标元素
            prev = curr;
            curr = curr->next;
        }
    }

    // 判断是否找到了元素
    if (!is_found) {
        // 走到这里说明没有找到
        printf("指定元素%d未找到，删除失败！\n", target);
        return false;
    }

    return true;
}

// 合并链表
LinkList combine_lists(LinkList list_1, LinkList list_2) {
    // 参数合法性检测
    arg_is_null(list_1);
    arg_is_null(list_2);

    // 使用链表1的头节点
    LinkList result_list = list_1;
    ptrToNode l1_node = list_1->next;
    ptrToNode l2_node = list_2->next;
    ptrToNode prev = result_list;

    while (l1_node != NULL && l2_node != NULL) {
        if (l1_node->elem < l2_node->elem) {
            // 添加链表1中的元素
            prev->next = l1_node;
            l1_node = l1_node->next;
        } else {
            // 添加链表2中的元素
            prev->next = l2_node;
            l2_node = l2_node->next;
        }
        prev = prev->next;
    }

    // 添加剩余的链
    prev->next = l1_node ? l1_node : l2_node;
    // 释放链表2头节点
    free(list_2);

    return result_list;
}

// 逆置链表
void reverse_list(LinkList list) {
    // 检测参数合法性
    arg_is_null(list);

    ptrToNode curr = list->next;
    ptrToNode prev;
    list->next = NULL;
    while (curr) {
        prev = curr;
        curr = curr->next;
        prev->next = list->next;
        list->next = prev;
    }
}

// 销毁一个链表
bool dispose_list(LinkList *p_list) {
    // 检测参数合法性
    arg_is_null(p_list);

    ptrToNode prev = *p_list;
    ptrToNode curr = (*p_list)->next;
    while (curr != NULL) {
        free(prev);  // 释放前置节点
        prev = curr;  // 移动前置节点
        curr = curr->next;  // 前移当前节点
    }
    // 释放最后一个节点
    free(prev);

    // 重置指针
    *p_list = NULL;

    return true;
}

// 返回链表的长度
int list_length(LinkList list) {
    // 参数合法性检测
    arg_is_null(list);

    int counts = 0;

    ptrToNode curr = list->next;
    while (curr != NULL) {
        counts++;
        curr = curr->next;
    }

    return counts;
}