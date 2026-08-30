# 226 - All Manhattan Distances

## Problem / 题目
Compute the sum of Manhattan distances over all pairs of $n$ points.

求 $n$ 个点所有点对的曼哈顿距离之和。

## Idea / 思路
The Manhattan distance separates into $x$ and $y$ contributions: the total is $\sum_{i<j}|x_i-x_j|+\sum_{i<j}|y_i-y_j|$. Each one-dimensional sum is computed by sorting the coordinate and using prefix sums: a sorted value at index $i$ contributes $a_i\cdot i-\text{prefix}$. The result can reach $\sim10^{19}$, so accumulate in 128-bit.

曼哈顿距离可分解为 $x$ 与 $y$ 两部分：总和为 $\sum_{i<j}|x_i-x_j|+\sum_{i<j}|y_i-y_j|$。每个一维和通过排序加前缀和求得：排序后下标 $i$ 处的值贡献 $a_i\cdot i-\text{前缀}$。结果可达 $\sim10^{19}$，故用 128 位累加。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
