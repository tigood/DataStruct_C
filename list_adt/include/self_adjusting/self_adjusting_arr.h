/*
自调整表的数组实现
*/
#include <stdio.h>
#include <stdbool.h>
#define MIN_LENGTH 5

typedef int ElementType;
typedef struct
{
    ElementType *Elements;  // 元素数组
    int ArrLength;  // 表长度
    int Capacity;  // 自调节表的容量
    int Front;  // 表头部下标
    int Rear;  // 表尾部下标
} SelfAdjustArr;

// 辅助函数：判断参数是否为有效参数
// 前置条件：传入一个自调节表的指针参数
// 后置条件：如果该参数为空则报错，并退出程序
void ArgIsNull(SelfAdjustArr *arg);

// 初始化一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：初始化该自调节表的指针
void InitSelfAdjustArr(SelfAdjustArr *, int);

// 清空一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：清空该自调节表
void EmptyTheAdjustArr(SelfAdjustArr *);

// 销毁一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：释放该自调节表
void DisposeTheAdjusArr(SelfAdjustArr *);

// 插入一个元素在自调整表的首部
// 前置条件：传入要插入的元素以及一个被插入的自调整表
// 后置条件：如果插入成功返回true，否则返回false
bool InsertToHeaderOfArr(ElementType, SelfAdjustArr *);

// 查找一个元素
// 前置条件：传入一个目标元素
// 后置条件：如果查找到了目标元素，就将该元素移到表头，并且返回true，否则什么也不做返回false
bool Find(ElementType, SelfAdjustArr *);

// 返回头部元素
// 前置条件：传入一个指定的自调节表指针
// 后置条件：返回表头元素
ElementType Front(SelfAdjustArr *);

// 返回头部元素
// 前置条件：传入一个指定的自调节表指针
// 后置条件：返回表尾元素
ElementType Rear(SelfAdjustArr *);

// 判断一个自调节表是否已满
bool IsFull(SelfAdjustArr *);

// 判断一个自调节表是否为空
bool IsEmpty(SelfAdjustArr *);

// 实现题目要求暂时写这么多功能就够了
