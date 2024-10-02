#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 100

// 多项式的常规ADT写法
// 其中CoeffArray是一个存储系数的数组，MaxDegree是表示该多项式的最高可能次
// HighPower 表示这个多项式的最高次，那么我们只需要注意系数数组中的0-HighPower
// typedef struct 
// {
//     int CoeffArray[MaxDegree + 1];
//     int HighPower

// } *polynomial;

// 我们可以用一个单链表来存储一个多项式，链表的每一个节点存储一个式子

typedef struct Item {
    int Coefficient;  // 系数
    int Exponent;  // 次数
} ElementType;

typedef struct Node *ptrToNode;

struct Node {
    ElementType item;
    ptrToNode next;
};

typedef ptrToNode Polynomial_Item;
typedef ptrToNode Polynomial; // 节点通过指数排序

// 初始化一个多项式
// 前置条件：传入一个未初始化的多项式
// 后值条件：多项式被初始化，拥有一个next指向NULL的头节点
void InitPolynomial(Polynomial* Poly) {
    (*Poly) = (Polynomial)malloc(sizeof(struct Node));

    if (*Poly != NULL) {
        (*Poly)->next = NULL;
    } else {
        printf("内存分配失败!\n");
        exit(EXIT_FAILURE);
    }
}

// 清空多项式内容
// 前置条件：传入一个初始化完成的多项式指针
// 后值条件：该多项式被清空
void ZeroPolynomial(Polynomial *Poly);

// 创建一个一个节点
// 前置条件：传入一个元素类型
// 后值条件：返回一个节点指针类型
Polynomial_Item CreateNode(ElementType item);

// 在多项式中添加式子
// 前置条件：传入一个指向多项式的指针，和一个要添加的元素
void AddItem(Polynomial *Poly, ElementType item);

void AddItemPlus(Polynomial *Poly, ElementType item);

// 输出多项式
// 前置条件：输入一个初始化的多项式
// 后值条件：将这个多项式的值打印出来
void PrintfPoly(Polynomial Poly);

// 将两个多项式相加
// 前置条件：传入两个多项式，和一个指向初始化多项式的指针
// 后置条件：将这两个多项式的和的指针赋值第三个指针
void AddPolynomials(Polynomial p1, Polynomial p2, Polynomial *sum);

// 将两个多项式相乘（时间复杂度O(N^2 * M^2)）
// 前置条件：传入两个多项式，和一个指向已经初始化多项式的指针
// 后置条件：将这个两个多项式的乘积
void MultPolynomials(Polynomial p1, Polynomial p2, Polynomial *result);

// 多项式相乘的优化版本（时间复杂度O(M^2 * N)）
void MultPolynomialsPlus(Polynomial p1, Polynomial p2, Polynomial *result);

// 计算多项式的幂
// 前置条件：传入一个多项式，和幂次数
// 后置条件：返回一个多项式，为结果
Polynomial FastPower(Polynomial F, int p);

int main()
{
    // 创建一个多项式
    Polynomial p1;
    // 初始化多项式
    InitPolynomial(&p1);
    // 添加元素
    ElementType one = {4, 5};
    ElementType two = {2, 3};
    AddItem(&p1, one);
    AddItem(&p1, two);
    printf("p1 = ");
    PrintfPoly(p1);
    Polynomial p2;
    InitPolynomial(&p2);
    ElementType three = {1, 2};
    ElementType four = {20, 23};
    AddItem(&p2, three);
    AddItem(&p2, four);
    printf("p2 = ");
    PrintfPoly(p2);
    Polynomial p3;
    InitPolynomial(&p3);
    AddPolynomials(p1, p2, &p3);
    printf("sum = ");
    PrintfPoly(p3);
    Polynomial p4;
    InitPolynomial(&p4);
    printf("mult = ");
    MultPolynomials(p1, p2, &p4);
    PrintfPoly(p4);

    return 0;
}

void ZeroPolynomial(Polynomial *Poly) {
    // 创建一个临时的指针
    Polynomial temp;
    while ((*Poly)->next != NULL) {
        temp = (*Poly)->next;
        (*Poly)->next = (*Poly)->next->next;
        free(temp);
    }
    (*Poly)->next = NULL;
}

Polynomial_Item CreateNode(ElementType item) {
    // 开辟一个节点空间
    Polynomial_Item newNode = (Polynomial_Item)malloc(sizeof(struct Node));
    // 为这个节点添加值
    newNode->item = item;
    newNode->next = NULL;
    return newNode;
}

void AddItem(Polynomial *Poly, ElementType item) {
    // 创建一个新的节点
    Polynomial_Item newNode = CreateNode(item);
    Polynomial_Item prev = *Poly;
    Polynomial_Item current = (*Poly)->next;

    // 找到插入位置
    while (current != NULL && current->item.Exponent > item.Exponent) {
        prev = current;
        current = current->next;
    }

    // 如果存在相同的指数，合并系数
    if (current != NULL && current->item.Exponent == item.Exponent) {
        current->item.Coefficient += item.Coefficient;
        free(newNode);
        if (current->item.Coefficient == 0) {
            // 如果系数为0，删除节点
            prev->next = current->next;
            free(current);
        }
    } else {
        // 插入新节点
        prev->next = newNode;
        newNode->next = current;
    }
}

void PrintfPoly(Polynomial Poly) {
    // 跳过第一个头节点
    Poly = Poly->next;
    // 如果多项式为空
    if (Poly == NULL) {
        printf("0\n");
        return;
    }
    // 输出多项式
    while (Poly != NULL) {
        printf("%dx^%d", Poly->item.Coefficient, Poly->item.Exponent);
        if (Poly->next != NULL) {
            printf(" + ");
        }
        Poly = Poly->next;
    }
    printf("\n");
}

void AddPolynomials(Polynomial p1, Polynomial p2, Polynomial *sum) {
    // 将目标多项式清空
    ZeroPolynomial(sum);
    // 添加第一个多项式中的值
    // 跳过头指针
    p1 = p1->next;
    while (p1 != NULL) {
        AddItem(sum, p1->item);
        p1 = p1->next;
    }
    // 添加第二个多项式中的值
    p2 = p2->next;
    while (p2 != NULL) {
        AddItem(sum, p2->item);
        p2 = p2->next;
    }
}

// 这个相乘的时间复杂度是O(n^2 * m^2)的
void MultPolynomials(Polynomial p1, Polynomial p2, Polynomial *result) {
    // 清空result多项式
    ZeroPolynomial(result);
    // 获取第一个多项式的有效值
    p1 = p1->next;

    // 通过循环来计算乘积
    while (p1 != NULL) {
        // 通过一个临时值获取第二个多项式中的值
        Polynomial_Item temp = p2->next;
        while (temp != NULL) {
            // 创建一个新变量来接受乘积
            ElementType newItem;
            newItem.Coefficient = p1->item.Coefficient * temp->item.Coefficient;
            newItem.Exponent = p1->item.Exponent + temp->item.Exponent;
            // 将新的多项式添加到result中
            AddItem(result, newItem);
            
            // 值向下一个式子
            temp = temp->next;
        }
        p1 = p1->next;
    }
}

// 相乘优化思路，使用一个数组存储相乘产生的结果
// 等最后全部计算完毕之后，这个数组中的下标就代表每一项的次数
// 这样这个数组中的式子就是有序的，在存储的时候就不需要遍历链表了，只需要m
void MultPolynomialsPlus(Polynomial p1, Polynomial p2, Polynomial *result) {
    // 初始化数组
    int coeffs[MAX_DEGREE + 1] = {0};
    // 获取第一个多项式的有效值
    p1 = p1->next;

    // 通过循环来计算乘积
    while (p1 != NULL) {
        // 通过一个临时值获取第二个多项式中的值
        Polynomial_Item temp = p2->next;
        while (temp != NULL) {
            // 计算新项的次数
            int newExponent = p1->item.Exponent + temp->item.Exponent;
            coeffs[newExponent] += p1->item.Coefficient * temp->item.Coefficient;
            temp = temp->next;
        }
        p1 = p1->next;
    }

    // 将结果一次性存储到链表中
    // 清空result多项式
    ZeroPolynomial(result);
    for (int i = MAX_DEGREE; i >= 0; i--) {
        // 只添加非零系数
        if (coeffs[i] != 0) {
            AddItem(result, (ElementType){coeffs[i], i});
        }
    }
}


// 优化方案二：将时间复杂度优化为O(M * N * log(MN))
// 思路：由于是两个多项式相乘的功能，所以相乘的两层循环是不可避免的，即M * N
//      要继续优化时间复杂度只能在AddItem上面做文章了，但是单链表有许多限制，所以我们需要通过二叉树或者跳表实现，这样这个一块就是对数级别的时间复杂度
// 上述的实现不需要通过修改MultPolynomials()方法，我们只需要对AddItem()方法
void AddItemPlus(Polynomial *Poly, ElementType item) {

}

// 使用快速幂法计算多项式的幂
Polynomial FastPower(Polynomial F, int p) {
    if (p == 0) {
        ElementType item = {1, 0}; // 代表常数1
        Polynomial result;
        InitPolynomial(&result);
        AddItem(&result, item);
        return result;
    }
    if (p == 1) {
        return F;
    }

    Polynomial halfPower = FastPower(F, p / 2);
    Polynomial result;
    MultPolynomials(halfPower, halfPower, &result);

    if (p % 2 != 0) {
        Polynomial temp;
        MultPolynomials(result, F, &temp);
        return temp;
    }
    
    return result;
}