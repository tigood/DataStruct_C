/*
使用循环数组实现队列adt
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10

// 病患类型
typedef struct _Patient {
	int id;
	char name[10];
} Patient;

typedef Patient ElementType;

// 顺序循环队列结构
typedef struct _Queue {
	ElementType data[MAXSIZE];  // 静态数组
	int rear, front;  // 队首和队尾
} Queue, *PQueue;

// 队列初始化
void init_queue(PQueue p_queue) {
	if (p_queue != NULL) {
		p_queue->front = p_queue->rear = 0;
	}
}

bool queue_is_empty(PQueue p_queue) {
	if (p_queue == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return p_queue->rear == p_queue->front;
}

// 入队
bool enqueue(PQueue p_queue, ElementType elem) {
	// 检测参数合法性
	if (p_queue == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	// 判满
	if ((p_queue->rear + 1) % MAXSIZE == p_queue->front) {
		// 走到这里说明就满了
		printf("队列已满，插入失败！\n");
		return false;
	}

	// 插入元素
	p_queue->data[p_queue->rear] = elem;
	p_queue->rear = (p_queue->rear + 1) % MAXSIZE;

	return true;
}

// 打印
void print_queue(PQueue p_queue) {
	if (p_queue == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	int curr_index = p_queue->front;
	if (queue_is_empty(p_queue)) {
		printf("当前没有患者排队！\n");
		return;
	}
	printf("患者依次为：\n");
	while (curr_index != p_queue->rear) {
		printf("%s    ", p_queue->data[curr_index].name);
		curr_index = (curr_index + 1) % MAXSIZE;
	}
	printf("\n");
}

// 出队
bool dequeue(PQueue p_queue, ElementType *target) {
	if (p_queue == NULL || target == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	// 判断队列是否为空
	if (queue_is_empty(p_queue)) {
		printf("队列为空！\n");
		return false;
	}

	*target = p_queue->data[p_queue->front];
	p_queue->front = (p_queue->front + 1) % MAXSIZE;

	return true;
}

// 展示队首元素
bool queue_front(PQueue p_queue, ElementType *result) {
	if (p_queue == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}
	if (queue_is_empty(p_queue)) {
		printf("队伍为空！\n");
		return false;
	}

	*result =  p_queue->data[p_queue->front];
	return true;
}

// 查看等待人数
int queue_items_count(PQueue p_queue) {
	if (p_queue == NULL) {
		fprintf(stderr, "参数传递错误！\n");
		exit(EXIT_FAILURE);
	}

	return (p_queue->rear - p_queue->front + MAXSIZE) % MAXSIZE;
}

int main(void) {
	int choice, id;
	char name[10];
	Patient patient;
	// 初始化一个队列
	Queue q;
	init_queue(&q);
	do {
		printf("***************************************\n");
	    printf("******欢迎进入就医排队管理系统*********\n");
	    printf("*\t请选择操作：*******************\n");
	    printf("*\t<1>:排队；*********************\n");
	    printf("*\t<2>:就诊；*********************\n");
	    printf("*\t<3>:查看即将就诊病人；*********\n");
	    printf("*\t<4>:显示等待人数；*************\n");
	    printf("*\t<5>:不再排队(依次看诊）；*****\n");
	    printf("*\t<0>:下班，退出运行；***********\n");
	    printf("***************************************\n");
	    printf("*请选择想要的操作（0-5）：*************\n");
	    scanf(" %d", &choice);

	    switch(choice) {
	    case 0:
	    	printf("下班时间到了，停止就诊！\n");
	    	break;
	    case 1:
	    	printf("请输入您的排序序号：\n");
	    	scanf(" %d", &patient.id);
	    	printf("请输入患者的姓名：\n");
	    	scanf(" %s", patient.name);
	    	if (enqueue(&q, patient)) {
	    		printf("排队成功！当前队伍中有%d个人\n", queue_items_count(&q));
	    	} else {
	    		printf("排队失败！\n");
	    	}
	    	break;
	    case 2:
	    	if (dequeue(&q, &patient)) {
	    		printf("%s患者就诊成功！患者id为：%d\n", patient.name, patient.id);
	    	} else {
	    		printf("当前没有患者排队！\n");
	    	}
	    	break;
	    case 3:
	    	if (queue_front(&q, &patient)) {
	    		printf("下一位患者名字为：%s,患者id为：%d\n", patient.name, patient.id);
	    	} else {
	    		printf("队伍为空，没有患者！\n");
	    	}
	    	break;
	    case 4:
	    	printf("当前队伍中有%d个患者！\n", queue_items_count(&q));
	    	break;
	    case 5:
	    	printf("不再排队，按下列顺序依次看诊：\n");
	    	print_queue(&q);
	    	break;
	    default:
	    	printf("请输入0-5之间的选项");
	    	break;
	    }
	} while (choice);

	printf("Done!\n");

	return 0;
}