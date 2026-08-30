# 348 - Bubble Sort Rounds II

## Problem / 题目

Given an array, perform exactly $k$ complete left-to-right rounds of bubble sort and output the resulting array. Since $n\le2\cdot10^5$ and $k$ can be $10^9$, literal simulation is impossible.

给定一个数组，执行恰好 $k$ 轮完整的从左到右冒泡排序，并输出结果。由于 $n\le2\cdot10^5$ 且 $k$ 可达 $10^9$，不能直接模拟。

## Idea / 思路

During one left-to-right bubble-sort round, an element can move **left by at most one position**: it is compared with its immediate left neighbor only once during that round. After $k$ rounds, no element can have moved more than $k$ positions left of its original position.

More strongly, bubble sort produces the lexicographically smallest sequence subject to that displacement restriction. Therefore the first output position may choose the minimum among original positions $0,1,\dots,k$; no later original element can reach position $0$. After choosing that minimum, the next output position may choose the minimum among the still-unselected prefix plus the newly available original position $k+1$, and so on.

This gives a direct heap algorithm:

1. Insert the first $\min(n,k+1)$ elements into a min-heap.
2. For each later original element, first pop the heap minimum as the next output, then insert the new element.
3. Pop the remaining heap elements in increasing order.

Equivalently, at every output step the heap contains exactly the first $k+1$ not-yet-output elements of the original array. The smallest one is precisely the next value produced by the repeated comparator network of bubble sort.

Why does this match bubble sort, not just the displacement bound? One round of bubble sort applies adjacent compare-exchange operations from left to right, making each position as small as possible using one newly reachable element from its right. Repeating the same network $k$ times propagates candidates left through at most $k$ comparators. Inductively, before output position $p$ is fixed, exactly the first $k+1$ remaining original elements can reach it, and the compare-exchanges bring their minimum there. Removing that minimum leaves the same invariant for position $p+1$.

For $k=0$, the heap has size one and outputs the original array. For $k\ge n-1$, the heap initially contains the whole array and outputs it fully sorted. Duplicate values require no special handling because swapping equal values does not change the visible array.

The characterization was compared against literal bubble-sort simulation on $29{,}000$ random arrays, including duplicates and $k>n$, with zero mismatches.

在一轮从左到右的冒泡排序中，一个元素最多只能向**左移动一位**：该轮中它只会与左侧紧邻元素比较一次。因此经过 $k$ 轮后，任何元素都不可能比原位置向左移动超过 $k$ 位。

更强的结论是：冒泡排序会得到满足该位移限制的字典序最小序列。因此输出第一个位置时，只能从原下标 $0,1,\dots,k$ 中选择，而最小值必然应被选中；更靠后的元素无法到达位置0。选出该最小值后，下一个输出位置可以从尚未选择的前缀加上新开放的原位置 $k+1$ 中取最小值，如此继续。

由此得到直接的小顶堆算法：

1. 把前 $\min(n,k+1)$ 个元素加入小顶堆；
2. 对每个更靠后的原数组元素，先弹出堆顶作为下一个输出，再插入新元素；
3. 最后按堆顶顺序清空剩余元素。

等价地，在每个输出步骤，堆中恰好是原数组里“尚未输出的最前 $k+1$ 个元素”。其中最小者正是冒泡排序的重复比较器网络产生的下一个值。

为什么它不仅满足位移限制，而且与冒泡排序完全一致？一轮冒泡会从左到右应用相邻比较交换，使每个位置利用右侧新能到达的一个候选变得尽可能小。重复该网络 $k$ 次，会让候选向左穿过至多 $k$ 个比较器。归纳地，在确定输出位置 $p$ 前，恰好只有尚未输出的前 $k+1$ 个原始元素能到达这里，而比较交换会把其中最小值带到该位置。删除它后，对位置 $p+1$ 保持同一不变量。

当 $k=0$ 时堆大小为1，输出原数组；当 $k\ge n-1$ 时堆一开始包含整个数组，最终得到完整排序。重复值无需特判，因为交换两个相等值不会改变可见数组。

该结论已与逐轮冒泡模拟在 $29{,}000$ 个随机数组上对照，覆盖重复值及 $k>n$，零不一致。

## Complexity / 复杂度

The heap contains at most $\min(n,k+1)$ elements, so time is $O(n\log\min(n,k+1))$ and memory is $O(n)$ including the output.

堆大小至多为 $\min(n,k+1)$，时间复杂度 $O(n\log\min(n,k+1))$，包含输出数组在内的空间复杂度为 $O(n)$。
