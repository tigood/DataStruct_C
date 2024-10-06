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



### 3.6 and 3.7 and 3.8

多项式的实现以及相关的操作：

实现代码文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/polynomial.c">polynomial.c</a>



### 3.9

任意精度整数运算包：

实现代码文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/big_int.c">bint_int.c</a>



### 3.10

**a**.这里就不写是实现代码了，简单讲一下优化思路

1. 最容易想到的方法就是遍历，根据输入的`M`值一次一次的遍历，这样的话时间复杂度就是`O(MN)`，对于一个较大的`M`是无法接受的。
2. 一种优化的思路：如果`M`大于一轮的情况下，我们直接遍历总会一轮一轮的经过原点，这些都是无意义的遍历，我们可以通过求模运算获得最后一次不到一轮的遍历，这样就省去了中途多余的一些遍历。即`move_counts = M % N`
3. 还有一种优化的思路：我们也可以通过反向移动的方法来减少移动的次数，这种实现就需要用到**双向链表**了。当移动的次数`M`大于`N`的一半并小于`N`的是时候，正向移动`M`次就等于反向的移动`N - M`次，即`move_counts = N - M`，这里要反向移动，判断条件为：`if((M > N / 2) && M < N)`

**b**.时间复杂度为：$O(N * min(N, M))$

**c**.如果`M`为$1$的话，那么运行时间就是线性的，取决于N，即$O(N)$。如果`N`很大的话，在这个程序中，这些节点都需要通过`free`来释放空间的话，这个释放空间的操作的占比就比较大了，就会影响一定的运行速度



### 3.11 and 3.12

代码实现文件：

<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/list.c">list.c</a>

3.12反转的另一种实现方式：

这种实现方式也可以，不过我没有在代码实现文件中写这一种，代码如下，可以参考代码研究一下思路。

```c
List ReverseList(List l) {
    Position CurrentPos, NextPos, PreviousPos;
    
    PreviousPos = NULL;
    CurrentPos = l; // 当前指向链表头
    while (CurrentPos != NULL) { // 只要当前节点不为 NULL
        NextPos = CurrentPos->next; // 保存当前节点的下一个节点
        CurrentPos->next = PreviousPos; // 反转当前节点的指针
        PreviousPos = CurrentPos; // 移动 PreviousPos 到当前节点
        CurrentPos = NextPos; // 移动到下一个节点
    }
    return PreviousPos; // 返回新的头节点（原链表的最后一个节点）
}
```



### 3.13 and 3.14

这两个题目涉及到了后续课程，目前我还没有学到，暂不实现

### 3.15

**a**.

实现代码文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/self_adjusting/self_adjusting_arr.c">self_adjusting_arr.c</a>

实现头文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/include/self_adjusting/self_adjusting_arr.h">self_adjusting_arr.h</a>

**b**.

实现代码文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/src/self_adjusting/self_adjusting_list.c">self_adjusting_list.c</a>

实现头文件：<a href="https://github.com/tigood/DataStruct_C/blob/main/list_adt/include/self_adjusting/self_adjusting_list.h">self_adjusting_list.h</a>

**c**.

emm..具体的论证就不写了，每次访问一个元素的时候都会将这个元素移动到表头，那么如果一个元素访问的频率较高，它就会经常被移到表头，虽然后面被访问的元素会将其顶开，但是访问频率高的由于会经常再被提到表头，这样访问频率高的都会表头附近循环，就会比较靠近表头。可能听着比较绕，但是意思是很简单的，细细品味一下。

### 3.16

**c**.

> 如果通过数组实现的话，删除操作的`O(N)`的，所以如果只是经过简单的判断，它可以达到一个`O(N^3)`的时间复杂度，但是实际上，只能达到`O(N^2)`的时间复杂度，因为如果对所有的元素都进行了删除操作，那么它就不需要进行外面的下一轮了。

**d**.

> 链表实现的时间复杂度也为`O(N^2)`

**e**.

> 先进行排序，再进行删除相同元素（这时候相同的元素都是相邻的，一次遍历就可以完成删除）

### 3.17

**a**.

> 优点有：程序容易编写，如果被删除的元素可能在之后重新被插入到相同的位置，那么懒惰删除可能省去插入的开销。
>
> 缺点有：使用了更多的空间，因为每个元素都有一个附加的域（通常占一个字节），并且被删除的元素的空间没有释放。

**b**.

实现头文件:
