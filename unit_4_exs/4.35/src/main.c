/*
层级遍历打印一棵树
*/
#include "../include/binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
先实现一个队列
*/
typedef struct QueueNode {
    Position treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Position node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    if (!queue->front) {
        queue->front = newNode;
    }
}

Position dequeue(Queue* queue) {
    if (!queue->front) return NULL;
    QueueNode* temp = queue->front;
    Position node = temp->treeNode;
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(temp);
    return node;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// 层级打印
void level_print(SearchTree tree) {
    if (tree == NULL) {
        printf("树为空，打印失败！\n");
        return;
    }

    // 初始化一个栈
    Queue* queue = createQueue();
    
    // 将根节点压入栈中
    enqueue(queue, tree);
    while (!isEmpty(queue)) {
        Position curr_node = dequeue(queue);
        printf("%d  ", retrieve(curr_node));
        if (curr_node->left)
        {
            enqueue(queue, curr_node->left);
        }
        if (curr_node->right) {
            enqueue(queue, curr_node->right);
        }
    }

    printf("\n");
}

// 层级打印puls版本，分层
void level_print_plus(SearchTree tree) {
    if (tree == NULL) {
        printf("树为空，打印失败！\n");
        return;
    }

    // 初始化一个队列
    Queue *queue = createQueue();
    // 将树根添加到队列中
    enqueue(queue, tree);

    while (!isEmpty(queue)) {
        int level_nodes_count = 0;
        QueueNode *temp = queue->front;

        // 计算当前层的节点数量
        while (temp) {
            level_nodes_count++;
            temp = temp->next;
        }

        // 访问当前层所有的节点
        for (int i = 0; i < level_nodes_count; i++) {
            Position curr_node = dequeue(queue);
            printf("%d   ", retrieve(curr_node));

            if (curr_node->left)
                enqueue(queue, curr_node->left);
            if (curr_node->right)
                enqueue(queue, curr_node->right);
        }
        printf("\n");
    }
}

int main(void) {
    // 初始化一颗树
    SearchTree tree = NULL;
    tree = insert_elem(3, tree);
    tree = insert_elem(2, tree);
    tree = insert_elem(5, tree);
    tree = insert_elem(1, tree);
    tree = insert_elem(4, tree);
    tree = insert_elem(7, tree);

    // 层级打印这颗树
    level_print(tree);

    printf("\n");

    level_print_plus(tree);

    return 0;
}
