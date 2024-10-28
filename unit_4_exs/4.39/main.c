#include <stdio.h>
#include "tree.h"

int main(void) {
    Tree tree = NULL;
    TreeNode first_node, seconde_node, third_node, fourth_node, fifth_node, sixth_node;
    // 初始化节点1
    first_node.elem = 'A';
    first_node.first_child = &seconde_node;
    first_node.next_sibling = NULL;
    // 初始化节点2
    seconde_node.elem = 'B';
    seconde_node.first_child = &fourth_node;
    seconde_node.next_sibling = &third_node;
    // 初始化节点3
    third_node.elem = 'C';
    third_node.first_child = &fifth_node;
    third_node.next_sibling = NULL;
    // 初始化节点4
    fourth_node.elem = 'D';
    fourth_node.first_child = NULL;
    fourth_node.next_sibling = &fifth_node;
    // 初始化节点5
    fifth_node.elem = 'E';
    fifth_node.first_child = NULL;
    fifth_node.next_sibling = &sixth_node;
    // 初始化节点6
    sixth_node.elem = 'F';
    sixth_node.first_child = NULL;
    sixth_node.next_sibling = NULL;
    tree = &first_node;

    print_tree(tree);
    return 0;
}
