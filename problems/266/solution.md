# 266 - Sliding Window Median

## Problem / 题目
For each window of $k$ elements, output the median (the smaller of the two middles when $k$ is even).

对每个 $k$ 元素窗口，输出中位数（$k$ 为偶时取较小的中间元素）。

## Idea / 思路
Maintain two multisets: a lower half and an upper half, kept balanced so the largest element of the lower half is the median. Each slide inserts one element and erases one (by value), after which the halves are rebalanced by moving a single element across the boundary.

维护两个多重集合：下半与上半，保持平衡使下半的最大元素为中位数。每次滑动插入一个、按值删除一个，之后通过在边界间移动一个元素来重新平衡。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
