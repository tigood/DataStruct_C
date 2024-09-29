# 数据结构与算法分析



## 第三章课后习题

### 3.1

打印单链表的程序：https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/list.c

### 3.2

> 如果仅仅使用基本的表操作的话，要实现该程序，需要用到两层循环，外层循环遍历`链表P`中的位置，内层循环根据外层循环提供的位置在`链表L`中寻找指定元素，由于是单链表，所以根据位置查找一个元素的平均时间复杂度为$O(n)$，而外层还有对于`链表P`的循环，所以整体的时间复杂度能达到$O(n^2)$

### 3.3

单链表的实现：https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/list.c

### 3.4 and 3.5

对两个已排序链表实现交并集操作:
<br/>
<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/list_more_func.c">list_more_func.c(功能实现部分)</a>
<br/>
<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/include/list_more_func.h">list_more_func.h(功能头文件)</a>
<br/>
<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/main.c">功能测试文件</a>