#include <stdio.h>
#include "hash_quad.h"

int main(void) {
    HashTable hash_table = create_hash_table_quad(20);
    insert_elem_hash_table_quad(hash_table, 2);
    insert_elem_hash_table_quad(hash_table, 5);
    insert_elem_hash_table_quad(hash_table, 1);
    insert_elem_hash_table_quad(hash_table, 8);
    insert_elem_hash_table_quad(hash_table, 6);
    insert_elem_hash_table_quad(hash_table, 7);
    delete_elem_hash_table_quad(hash_table, 8);
    hash_table = rehash_hash_table_quad(hash_table);
    delete_elem_hash_table_quad(hash_table, 6);

    destroy_hash_table_quad(&hash_table);
    return 0;
}
