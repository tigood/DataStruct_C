#include "../include/list_lazy_del.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    List my_list;
    init_list(&my_list);
    insert_list_header(4, my_list);
    insert_list_header(3, my_list);
    insert_list_header(4, my_list);
    insert_list_header(3, my_list);
    insert_list_header(2, my_list);
    insert_list_header(1, my_list);
    printf("链表实际有%d个元素，其中%d个被标记为已删除，%d个是正常的元素\n", my_list->all_item_counts, my_list->deleted_item_counts, my_list->normal_item_counts);
    print_list(my_list);
    delete_item_lazy(2, my_list);
    printf("链表实际有%d个元素，其中%d个被标记为已删除，%d个是正常的元素\n", my_list->all_item_counts, my_list->deleted_item_counts, my_list->normal_item_counts);
    print_list(my_list);
    insert_list_by_postion(2, my_list, 2);
    print_list(my_list);
    printf("链表实际有%d个元素，其中%d个被标记为已删除，%d个是正常的元素\n", my_list->all_item_counts, my_list->deleted_item_counts, my_list->normal_item_counts);
    delete_item_lazy(1, my_list);
    delete_item_lazy(3, my_list);
    print_list(my_list);
    printf("链表实际有%d个元素，其中%d个被标记为已删除，%d个是正常的元素\n", my_list->all_item_counts, my_list->deleted_item_counts, my_list->normal_item_counts);
    insert_list_by_postion(3, my_list, 2);
    print_list(my_list);
    insert_list_by_postion(10, my_list, 2);
    print_list(my_list);
    insert_list_by_postion(1, my_list, 1);
    print_list(my_list);
    return 0;
}