#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElementType int
#define M 5  // 稀疏矩阵行数
#define N 6  // 稀疏矩阵列数
#define MAXSIZE 100  // 稀疏矩阵中非零元素个数最大值

typedef struct {
	int r;  // 元素行号，取单词row首字母
	int c;  // 元素列号，取单词col首字母
	ElementType d;  // 元素值，取data首字母
} Triple;

typedef struct {
	Triple data[MAXSIZE];  // 三元组表，以行为主序存入一维向量data中
	int rows;  // 矩阵总行数
	int cols;  // 矩阵总列数
	int nums;  // 矩阵中非零元素的个数
} TsMatrix;  // 三元组顺序表的类型

// 从一个二维矩阵创建其三元组表示的运算算法
void create_mat(TsMatrix *t, ElementType arr[M][N]) {
	t->rows = M;
	t->cols = N;
	t->nums = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != 0) {
				t->data[t->nums].r = i;
				t->data[t->nums].c = j;
				t->data[t->nums].d = arr[i][j];
				t->nums++;
			}
		}
	}
}

// 三元组元素赋值运算算法
bool set_val(TsMatrix *t, ElementType elem, int rs, int cs) {
	int k = 0;

	if (rs >= t->rows || cs >= t->cols || elem == 0 || rs < 0 || cs < 0)
		return false;

	while (k < t->nums && rs > t->data[k].r)
		k++;
	while (k < t->nums && rs == t->data[k].r && cs > t->data[k].c)
		k++;

	if (t->data[k].r == rs && t->data[k].c == cs)
		t->data[k].d = elem;
	else {
		for (int i = t->nums - 1; i >= k; i--) {
			t->data[i + 1].r = t->data[i].r;
			t->data[i + 1].c = t->data[i].c;
			t->data[i + 1].d = t->data[i].d;
		}
		t->data[k].r = rs;
		t->data[k].c = cs;
		t->data[k].d = elem;
		t->nums++;
	}

	return true;
}

bool assign(TsMatrix t, int *elem, int rs, int cs) {
	int k = 0;
	if (rs >= t.rows || cs >= t.cols || rs < 0 || cs < 0)
		return false;

	while (k < t.nums && rs > t.data[k].r)
		k++;
	while (k < t.nums && rs == t.data[k].r && cs > t.data[k].c)
		k++;
	if (t.data[k].r == rs && t.data[k].c == cs) {
		*elem = t.data[k].d;
		return true;
	} else
		return false;
}

// 输出三元组运算算法
bool disp_mat(TsMatrix t) {
	if (t.nums <= 0)
		return false;

	printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
	printf("--------------------------------------------\n");
	for (int i = 0; i < t.nums; i++)
		printf("\t%d\t%d\t%d\n", t.data[i].r, t.data[i].c, t.data[i].d);
	return true;
}

int main(void) {
	TsMatrix t;
	ElementType elem;
	ElementType array[M][N] = {
		{0, 12, 9, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, -2, 1, 0, 0, 0},
		{0, 0, 6, 0, 0, 0},
		{0, 8, 0, 0, 0, 0},
	};
	int i = 0, rn, cn, choice = 0;
	do{ 
		printf("************稀疏矩阵的三元组实现***************\n");
		printf("************1-----创建稀疏矩阵三元组表示*******\n");
		printf("************2-----三元组元素的赋值*************\n");
		printf("************3-----读取矩阵指定位置数值*********\n");
		printf("************0-----退出*************************\n");
		printf("请输入想要进行的运算(0-3)：\n");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1:
				create_mat(&t, array);
				printf("该稀疏矩阵为：\n");
				disp_mat(t);
				break;
			case 2:
				printf("请输入行号，列号和数值：\n");
				scanf(" %d", &rn);
				scanf(" %d", &cn);
				scanf(" %d", &elem);
				if (set_val(&t, elem, rn, cn)) {
					printf("插入成功！该矩阵为：\n");
					disp_mat(t);
				} else
					printf("插入位置不合理！\n");
                break;
			case 3:
				printf("请输入行号，列号：\n");
				scanf(" %d", &rn);
				scanf(" %d", &cn);
				if (assign(t, &elem, rn, cn))
					printf("第%d行第%d列的元素为：%d\n", rn, cn, elem);
				else
					printf("位置参数不合理！\n");
                break;
            case 0:
				printf("退出！\n");         
				break;
			default:printf("输入的选项不正确，应为(0-3)，请重试！\n");
				break;
	  	}
  	} while(choice);

  	return 0;
}