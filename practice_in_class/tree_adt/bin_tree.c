#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct node {
    ElementType data;
    struct node *lchild, *rchild;
} BinTNode, *BinTree;

// 创建二叉树
BinTree create_bin_tree() {
    char ch;
    BinTree T;
    printf("请输入一个树序列：\n");

    ch = getchar(); // 从输入流中读取字符
    if (ch == '\n') {
        return NULL;  // 输入结束，返回 NULL
    }

    if (ch == '#') {
        T = NULL;  // 空节点
    } else {
        // 创建节点
        T = malloc(sizeof(BinTNode));
        if (!T) {
            fprintf(stderr, "新节点开辟失败！\n");
            exit(EXIT_FAILURE);
        }
        T->data = ch;                  // 设置节点数据
        T->lchild = create_bin_tree(); // 先递归创建左子树
        T->rchild = create_bin_tree(); // 再递归创建右子树
    }
    return T;
}

// 打印二叉树
bool print_bin_tree(BinTree tree) {
    if (!tree)
        return false;

    printf("%c", tree->data);
    if (tree->lchild || tree->rchild) {
        printf("(");
        print_bin_tree(tree->lchild);
        if (tree->rchild)
        printf(",");
        print_bin_tree(tree->rchild);
        printf(")");
    }
    return true;
}

// 前序遍历
bool prePrint(BinTree tree) {
    if (tree) {
        printf("%c\t\t", tree->data);
        prePrint(tree->lchild);
        prePrint(tree->rchild);
    }

    return true;
}

// 中序遍历
bool inPrint(BinTree tree) {
    if (tree) {
        inPrint(tree->lchild);
        printf("%d\t\t", tree->data);
        inPrint(tree->rchild);
    }

    return true;
}

// 后序遍历
bool afterPrint(BinTree tree) {
    if (tree) {
        afterPrint(tree->lchild);
        afterPrint(tree->rchild);
        printf("%c\t\t", tree->data);
    }

    return true;
}

// 创建二叉排序树
bool create_bin_sort_tree(BinTree *p_tree, ElementType e) {
    // 如果为空，就创建节点
    if (!(*p_tree)) {
        // 开辟一个新节点
        *p_tree = (BinTNode *)malloc(sizeof(BinTNode));
        if (*p_tree == NULL) {
            fprintf(stderr, "空间开辟失误!\n");
            return false;
        }
        (*p_tree)->data = e;
        (*p_tree)->lchild = (*p_tree)->rchild = NULL;
        return true;
    } else {
        if ((*p_tree)->data >= e)
            return create_bin_sort_tree(&(*p_tree)->lchild, e);
        else
            return create_bin_sort_tree(&(*p_tree)->rchild, e);
    }
}

// 删除树
BinTree destroy_tree(BinTree tree) {
    // 首先对子树进行非空判断，防止进入左右子树的无限转换
    if (tree != NULL) {
        // 后序遍历
        destroy_tree(tree->lchild);
        destroy_tree(tree->rchild);
        free(tree);
    }

    return tree;
}

// AB##CD###
int main()
{   BinTree T = NULL;
    BinTNode *p;
    ElementType e=0;
    int choice = 0;
    do
    {
        printf("****************二叉树的操作**************\n");
        printf("**************1-插入（排序树）*************\n");
        printf("**************2-先序遍历******************\n");
        printf("**************3-中序遍历******************\n");
        printf("**************4-后序遍历******************\n");
        printf("**************5-删除树********************\n");
        printf("**************6-一次性生成树**************\n");
        printf("**************0-退出**********************\n");
        printf("请输入要进行的操作：\n");
        rewind(stdin);
        scanf("%d", &choice);
        getchar();
        switch (choice)
        { case 1:
            printf("请输入要插入的数据：\n");
            scanf(" %d", &e);
            create_bin_sort_tree(&T, e);
            break;
          case 2:
            printf("先序遍历为：\n");
            prePrint(T);               //递归遍历
            printf("\n");
            break;
          case 3:
            printf("中序遍历为：\n");
            inPrint(T);               //递归遍历
            printf("\n");
            break;
          case 4:
            printf("后序遍历为：\n");
            afterPrint(T);               //递归遍历
            printf("\n");
            break;
          case 5:
            printf("删除树：\n");
            destroy_tree(T);
            printf("空树\n");        
            printf("\n");
            break;
          case 6:
            printf("请输入树中的元素，#代表空!\n");
            fflush(stdin);
            T=create_bin_tree();
            print_bin_tree(T);
            printf("\n构造完毕,遍历查看！\n");
            break;
         case 0: 
            printf("退出！\n");
            break;
         default:
            printf("请输入0-6！\n");
            break;
        }
    } while (choice);

    return 0;
}
