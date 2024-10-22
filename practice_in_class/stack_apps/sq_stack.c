/*
使用动态数组实现顺序栈
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 3  // 初始内存
#define INCREAMENT 10  // 每次增长这么多

typedef int ElementType;

typedef struct {
    ElementType *base;
    size_t stack_size;
    ElementType *top;
} SqStack, *PSqStack;

// 栈的初始化
bool init_stack(PSqStack p_stack) {
    p_stack->base = p_stack->top = (ElementType *)malloc(sizeof(ElementType) * MAXSIZE);
    // 判断空间是否开辟成功
    if (!p_stack->top) {
        fprintf(stderr, "空间开辟错误！\n");
        return false;
    }

    // 初始化栈
    p_stack->stack_size = 3;
    return true;
}

// 判断栈是否为空
bool is_empty(PSqStack p_stack) {
    if (p_stack != NULL) {
        return p_stack->base == p_stack->top;
    }

    fprintf(stderr, "参数传递错误！\n");
    return false;
}

// 判断栈是否已满
bool is_full(PSqStack p_stack) {
    return (p_stack->top - p_stack->base) == p_stack->stack_size;
}

// 为栈增加容量
bool incrent_capacity(PSqStack p_stack) {
    // 计算新内存的大小
    size_t new_size = p_stack->stack_size + INCREAMENT;

    // 开辟新的空间
    ElementType *new_base = (ElementType *)realloc(p_stack->base, sizeof(ElementType) * new_size);
    if (new_base == NULL) {
        fprintf(stderr, "空间开辟失败！\n");
        return false;
    }

    p_stack->base = new_base;
    p_stack->top = p_stack->base + p_stack->stack_size;
    p_stack->stack_size = new_size;

    return true;
}

// 入栈
bool push(PSqStack p_stack, ElementType elem) {
    // 判断栈是否为满
    if (is_full(p_stack)) {
        // 如果栈满就扩容栈
        printf("栈已满，正在扩容中...\n");
        if (incrent_capacity(p_stack))
        {
            printf("扩容成功！\n");
        }
    }
    *p_stack->top++ = elem;

    return true;
}

// 打印栈
void print_stack(PSqStack p_stack) {
    // 判断栈是否为空
    if (is_empty(p_stack)) {
        printf("栈为空打印失败！\n");
        return;
    }

    for (ElementType *curr = p_stack->base; curr != p_stack->top; curr++) {
        printf("%d  ", *curr);
    }
    printf("\n");
}

// 弹出元素
bool pop(PSqStack p_stack, ElementType *result) {
    if (is_empty(p_stack)) {
        // 走到这里说明栈为空，不能弹出
        fprintf(stderr, "栈为空，不能进行弹出操作");
        return false;
    }
    *result = *(--p_stack->top);

    return true;
}

ElementType top(SqStack stack) {
    if (is_empty(&stack)) {
        // 走到这里说明栈为空，不能弹出
        fprintf(stderr, "栈为空，不能进行弹出操作");
        exit(EXIT_FAILURE);
    }

    return *(--stack.top);
}

// 进制转化函数
void convert_base(int number, int base) {
    // 判断输入的数字
    if (number == 0) {
        printf("结果是：0\n");
        return;
    }

    // 初始化一个栈
    SqStack result_stack;
    init_stack(&result_stack);

    while (number > 0) {
        // 计算余数
        int temp = number % base;
        // 将余树压入栈中
        push(&result_stack, temp);
        number /= base;
    }

    printf("转换结果为：\n");
    // 从栈中打印出结果
    while (!is_empty(&result_stack)) {
        int digit;
        pop(&result_stack, &digit);
        if (digit < 10) {
            printf("%d", digit);  // 输出数字
        } else {
            printf("%c", 'A' + (digit - 10));
        }
    }
    printf("\n");
}

void main()
{
	SqStack S;//创建栈对象
	int choice=0;
	int e;
	int num,d;
	init_stack(&S);//调用初始化函数
	do
	{
		printf("*************栈的基本操作**************\n");
		printf("**************1.创建栈*****************\n");
		printf("**************2.入栈*******************\n");
		printf("**************3.出栈*******************\n");
		printf("**************4.取栈顶元素*************\n");
		printf("**************5.判断栈空***************\n");
		printf("**************6.应用：数制转换*********\n");
		printf("**************0.退出*******************\n");
		printf("请输入要进行的操作：\n");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			init_stack(&S);
			break;
		case 2:
			printf("请输入要插入的数据：\n");
			scanf(" %d",&e);
			push(&S,e);
			print_stack(&S);
			break;
		case 3:
			if(pop(&S,&e))
			{printf("删除的数据为%d\n",e);}
			print_stack(&S);
			break;
		case 4:
			printf("栈顶数据为%d\n",top(S));
			break;
		case 5:
			if(is_empty(&S))
			  printf("空栈！\n");
			else
			  printf("栈不空！\n");
			break;
        case 6:
			printf("请输入待转换：\n");
			scanf(" %d",&num);
			printf("请输入目标进制：\n");
			scanf(" %d",&d);
			printf("将十进制数%d转换为%d进制数，结果为：\n",num,d);
			convert_base(num,d);
			break;
		case 0:
			printf("退出！\n");
			break;
		default:
			printf("只能输入0-5！\n");
			break;

		}
	}while(choice);
	system("pause");
}