#include "link_list.h"
#include <stdio.h>
#include <stdbool.h>

int choose_menu_func() {
    int choose;
    printf("----------------- 单链表操作 ------------------\n");
    printf("----------------- 1.   建表 ------------------\n");
    printf("----------------- 2.   判空 ------------------\n");
    printf("----------------- 3.  求表长 ------------------\n");
    printf("----------------- 4.   查找 ------------------\n");
    printf("----------------- 5.   插入 ------------------\n");
    printf("----------------- 6.   删除 ------------------\n");
    printf("----------------- 7.   归并 ------------------\n");
    printf("----------------- 8.   销毁 ------------------\n");
    printf("----------------- 9.   逆序 ------------------\n");
    printf("----------------- 0.   退出 ------------------\n");
    scanf("%d", &choose);
    getchar();
    return choose;
}

void test_create_list(LinkList list) {
    printf("请输入要创建链表的长度：");
    int length;
    scanf("%d", &length);
    getchar();
    printf("请选择插入方法，头插入还是尾插入，还是产生随机数字并尾插入，依次为A B C\n");
    char select;
    scanf("%c", &select);
    switch (select)
    {
    case 'A':
        create_list_front(list, length);
        break;
    case 'B':
        create_list_rear(list, length);
        break;
    case 'C':
        create_list_rear_random(list, length);
        break;
    default:
        printf("只有A B C选项\n");
        return;
    }
    print_list(list);
}

void test_is_empty(LinkList list) {
    if (is_empty(list)) {
        printf("该表为空！\n");
    } else {
        printf("该表不为空！\n");
    }
}

void test_get_length(LinkList list) {
    printf("线性表的长度为：%d\n", list_length(list));
}

void test_find_item(LinkList list) {
    printf("请选择查找方式：A按序号查找  B按值查找\n");
    char select;
    int position, result, target;
    scanf("%c", &select);
    switch (select)
    {
    case 'A':
        printf("请输入你要查找的元素的位置：");
        scanf("%d", &position);
        if (get_elem_by_position(list, position, &result)) {
            printf("位置为%d的元素的值是：%d\n", position, result);
        } else {
            printf("位置为%d的元素不存在！\n", position);
        }
        break;
    case 'B':
        printf("请输入要查找的元素的数值：");
        scanf("%d", &target);
        result = find_node_by_value(list, target);
        if (result > 0) {
            printf("第一个数值为%d的元素的位置是：%d\n", target, result);
        } else {
            printf("数值为%d的元素不存在\n", target);
        }
        break;
    default:
        printf("只有A B两个选项");
        break;
    }
}

void test_insert(LinkList list) {
    int value, position;
    printf("请输入要插入的元素的值：");
    scanf("%d", &value);
    printf("请输入要插入的位置：");
    scanf("%d", &position);
    if (insert_node_by_position(list, position, value)) {
        printf("节点插入成功！\n");
        print_list(list);
    }
    else
    {
        printf("节点插入失败！\n");
    }
}

void test_delete(LinkList list) {
    char select;
    int position, target, result;
    printf("请选择删除的方法：A按位置删除，B按数值删除，C删除给定数值的所有节点：");
    scanf("%c", &select);
    switch (select)
    {
    case 'A':
        printf("请输入要删除元素的位置：");
        scanf("%d", &position);
        if (delete_node_by_position(list, position, &result)) {
            printf("删除了第%d个元素，值为：%d\n", position, result);
            print_list(list);
        } else {
            printf("删除失败，未找到该位置的元素!\n");
        }
        break;
    case 'B':
        printf("请输入要删除元素的数值：");
        scanf("%d", &target);
        if (delete_node_by_value(list, target)) {
            printf("第一个%d元素删除成功！\n", target);
            print_list(list);
        } else {
            printf("删除失败，未找到指定数值元素！\n");
        }
        break;
    case 'C':
        printf("请输入要删除元素的数值：");
        scanf("%d", &target);
        if (delete_nodes_by_value(list, target)) {
            printf("全部的%d元素删除成功！\n", target);
            print_list(list);
        } else {
            printf("删除失败，未找到指定数值元素！\n");
        }
        break;
    default:
        printf("选项只有A B C\n");
        break;
    }
}

void test_combine(LinkList list_1, LinkList list_2) {
    int len;
    printf("请输入链表1的长度：");
    scanf("%d", &len);
    create_list_rear(list_1, len);
    print_list(list_1);
    printf("请输入链表2的长度：");
    scanf("%d", &len);
    create_list_rear(list_2, len);
    print_list(list_2);
    list_1 = combine_lists(list_1, list_2);
    printf("两个链表合并后：");
    print_list(list_1);
}

void test_dispose(LinkList list) {
    if (dispose_list(&list)) {
        printf("销毁成功！\n");
    } else {
        printf("销毁失败！\n");
    }
}

void test_reverse(LinkList list) {
    reverse_list(list);
    printf("逆序成功！\n");
    print_list(list);
}

int main() {
    LinkList l, l1, l2;
    l = init_list_return();
    l1 = init_list_return();
    l2 = init_list_return();
    int choose;
    do {
        choose = choose_menu_func();
        switch (choose)
        {
        case 1:
            test_create_list(l);
            break;
        case 2:
            test_is_empty(l);
            break;
        case 3:
            test_get_length(l);
            break;
        case 4:
            test_find_item(l);
            break;
        case 5:
            test_insert(l);
            break;
        case 6:
            test_delete(l);
            break;
        case 7:
            test_combine(l1, l2);
            break;
        case 8:
            test_dispose(l);
            break;
        case 9:
            test_reverse(l);
            break;
        case 0:
            printf("退出！\n");
            break;
        default:
            printf("请输入合理的选项！\n");
            break;
        }

    } while (choose);

    return 0;
}