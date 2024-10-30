#include <stdio.h>
#include "hash_sep.h"

int main(void) {
    HashTable hash_table = create_hash_table(10);
    for (int i = 0; i < 10; i++) {
        insert_elem_hash_table(hash_table, i * i);
    }
    delete_node_hash_table(hash_table, 4);
    destroy_hash_table(&hash_table);
    return 0;
}
