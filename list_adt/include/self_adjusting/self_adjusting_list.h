/*
自调整表的链表实现
*/
#include <stdbool.h>

struct Node;
struct SelfAdjustListRecord;

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef struct SelfAdjustListRecord *SelfAdjustList;

struct Node
{
    ElementType elem;
    PtrToNode next;
};

struct SelfAdjustListRecord {
    PtrToNode pFront;
    int length;
};

// 辅助函数：判断参数是否为有效参数
// 前置条件：传入一个自调节表的指针参数
// 后置条件：如果该参数为空则报错，并退出程序
void ArgIsNull(SelfAdjustList);

// 初始化一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：初始化该自调节表的指针
void InitSelfAdjustList(SelfAdjustList *);

// 清空一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：清空该自调节表
void EmptyTheAdjustList(SelfAdjustList);

// 销毁一个自调整表
// 前置条件：传入一个自调节表的指针
// 后置条件：释放该自调节表
void DisposeTheAdjusList(SelfAdjustList);

// 插入一个元素在自调整表的首部
// 前置条件：传入要插入的元素以及一个被插入的自调整表
// 后置条件：如果插入成功返回true，否则返回false
bool InsertToHeaderOfList(ElementType, SelfAdjustList);

// 查找一个元素
// 前置条件：传入一个目标元素
// 后置条件：如果查找到了目标元素，就将该元素移到表头，并且返回true，否则什么也不做返回false
bool Find(ElementType, SelfAdjustList);

// 返回头部元素
// 前置条件：传入一个指定的自调节表指针
// 后置条件：返回表头元素
ElementType Front(SelfAdjustList);

// 判断一个自调节表是否为空
bool IsEmpty(SelfAdjustList);

// 实现题目要求暂时写这么多功能就够了
