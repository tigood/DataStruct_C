#include "list_lazy_del.h"
#include <stdio.h>
#include <stdlib.h>

// 参数合法性检测
void arg_is_null(List l) {
    if (l == NULL) {
        fprintf(stderr, "参数传递错误！\n");
        exit(EXIT_FAILURE);
    }
}

// 初始化链表
void init_list(List *p_list) {
    // 检测参数合法性
    arg_is_null(*p_list);

    // 尝试为链表开辟空间
    *p_list = (List)malloc(sizeof(struct ListRecord));
    if (*p_list == NULL) {
        fprintf(stderr, "链表空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 尝试为头节点开辟空间
    ptrToNode header_node = (ptrToNode)malloc(sizeof(struct Node));
    if (header_node == NULL) {
        fprintf(stderr, "头节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化头节点
    header_node->next = NULL;

    // 初始化链表
    (*p_list)->p_front = header_node;
    (*p_list)->all_item_counts = 0;
    (*p_list)->deleted_item_counts = 0;
    (*p_list)->normal_item_counts = 0;
}

// 清空一个链表
void empty_list(List l) {
    // 检测参数合法性
    arg_is_null(l);

    if (!is_empty(l)) {
        // 如果不为空，就清空链表
        ptrToNode curr = l->p_front->next;
        ptrToNode temp;
        while (curr != NULL) {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

// 销毁一个链表
void dispose_list(List *p_list) {
    // 检测参数合法性
    arg_is_null(*p_list);

    // 如果链表不为空就先清空链表
    if (!is_empty(*p_list)) {
        empty_list(*p_list);
    }

    // 释放头节点
    if ((*p_list)->p_front != NULL) {
        free((*p_list)->p_front);
    }

    // 释放链表例程
    free(*p_list);

    // 将指针置为空
    *p_list = NULL;
}

// 在链表的头部插入一个元素
void insert_list_header(Item elem, List l) {
    // 参数合法性检测
    arg_is_null(l);

    // 创建一个新的节点
    ptrToNode newNode = (ptrToNode)malloc(sizeof(struct Node));
    
    // 检测是否创建成功
    if (newNode == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化新节点
    newNode->element = elem;
    newNode->next = NULL;
    newNode->is_del = false;

    // 如果链表为空，直接连接在头节点的后面
    newNode->next = l->p_front->next;
    l->p_front->next = newNode;

    // 更新链表的其他信息
    l->all_item_counts++;
    l->normal_item_counts++;
}

// 将一个指定元素插入到指定位置
bool insert_list_by_postion(Item elem, List l, int postion) {
    // 检验参数合法性
    arg_is_null(l);

    // 检验位置合法性
    if (postion <= 0 || postion > l->normal_item_counts + 1) {
        fprintf(stderr, "位置插入不合理!\n");
        return false;
    }

    ptrToNode curr = l->p_front->next;
    ptrToNode prev = l->p_front;
    while (curr != NULL && postion > 1)
    {
        // 如果当前的元素是未被标记删除的就算作正常移动了一次
        if (!curr->is_del) {
            postion--;
        } 
        prev = curr;
        curr = curr->next;
    }

    // 遍历这之后的被标记为删除的值
    while (curr != NULL && curr->is_del)
    {
        // 如果找到的相同的值
        if (curr->element == elem) {
            curr->is_del = false;

            // 更改记录
            l->deleted_item_counts--;
            l->normal_item_counts++;
            puts("更改标志了！");  // 调试信息
            return true;
        }
        curr = curr->next;
    }

    // 如果没有找到相同值的元素就插入
    // 创建新节点
    ptrToNode newNode = (ptrToNode)malloc(sizeof(struct Node));

    // 判断是否创建成功
    if (newNode == NULL) {
        fprintf(stderr, "节点空间开辟失败！\n");
        exit(EXIT_FAILURE);
    }

    // 初始化新节点
    newNode->element = elem;
    newNode->next = NULL;
    newNode->is_del = false;

    // 将新节点插入链表
    newNode->next = curr;
    prev->next = newNode;

    // 更新链表信息
    l->all_item_counts++;
    l->normal_item_counts++;
    return true;
}

// 遍历链表删除所有被标记的元素
void rm_deleted_items(List l) {
    // 检测参数合法性
    arg_is_null(l);

    // 遍历链表删除被标记的元素
    ptrToNode curr = l->p_front->next;
    ptrToNode prev = l->p_front;
    while (curr != NULL) {
        if (curr->is_del) {
            // 移除当前的元素
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
            // 更新链表信息
            l->all_item_counts--;
            l->deleted_item_counts--;
        }
        else
        {
            // 向前移动
            prev = curr;
            curr = curr->next;
        }
    }
}

// 删除指定的元素
void delete_item_lazy(Item target, List l) {
    // 参数合法性检测
    arg_is_null(l);

    // 查找是否有指定元素
    ptrToNode temp = l->p_front->next;
    while (temp != NULL)
    {
        if (temp->element == target)
            break;
        temp = temp->next;
    }

    // 判断是否找到了
    if (temp) {
        // 更新信息
        temp->is_del = true;
        l->deleted_item_counts++;
        l->normal_item_counts--;
        
        // 判断是否该清理了
        if (l->deleted_item_counts >= (l->all_item_counts / 2)) {
            // 执行清理
            rm_deleted_items(l);
        }
    }
}

// 判断链表是否为空(不管是否被标记)
bool is_empty(List l) {
    return l->all_item_counts == 0;
}

// 检测正常元素部分是否为空
bool is_empty_nomal(List l) {
    return l->normal_item_counts == 0;
}

// 打印链表
void print_list(List l) {
    // 参数合法性检测
    arg_is_null(l);

    ptrToNode curr = l->p_front->next;
    while (curr != NULL)
    {
        if (!curr->is_del) {
            printf("%d ", curr->element);
        }
        curr = curr->next;
    }
    printf("\n");
}