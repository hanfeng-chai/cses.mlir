# 033 - Stick Lengths

## Problem / 题目

Make all $n$ sticks the same length; changing a stick by $d$ units costs $d$. Minimise the total cost.

把 $n$ 根木棍变成相同长度；把一根木棍改变 $d$ 个单位花费 $d$。求最小总花费。

## Idea / 思路

The target length that minimises the sum of absolute differences is the **median** of the lengths. Sort the sticks, take the middle element as the target, and sum $|p_i - \text{median}|$. (Intuitively, moving the target off the median increases the distance to at least half the sticks by as much as it decreases the others.)

使最小化绝对差之和的目标长度是各长度的**中位数**。把木棍排序，取中间元素作为目标，累加 $|p_i - \text{中位数}|$。（直观地说，把目标移离中位数，会让至少一半木棍增加的距离不小于另一半减少的距离。）

## Complexity / 复杂度

Sorting dominates, so the time is $O(n \log n)$.

排序是主要开销，因此时间为 $O(n \log n)$。
