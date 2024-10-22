#include "../include/search_tree.h"
#include <stdio.h>
#include <stdlib.h>

void print_tree(SearchTree tree) {
    if (tree != NULL) {
        print_tree(tree->left);
        printf("x = %d, y = %d\n", tree->x, tree->y);
        print_tree(tree->right);
    }
}

int main(void) {
    SearchTree tree = NULL;
    tree = insert_elem(3, tree);
    tree = insert_elem(2, tree);
    tree = insert_elem(4, tree);
    tree = insert_elem(5, tree);
    tree = insert_elem(1, tree);
    tree = set_x_position(tree);
    tree = set_y_position(tree);
    print_tree(tree);
    generate_tree_instructions(tree);
    make_empty(tree);

    return 0;
}