# 298 - Course Schedule II

## Problem / 题目
Find a topological order of $n$ courses that completes course $1$ as early as possible, then course $2$, and so on.

求 $n$ 门课的拓扑序，使课 $1$ 尽量早完成，其次课 $2$，依此类推。

## Idea / 思路
Reverse all edges and compute the lexicographically **largest** topological order of the reversed graph using a max-heap (Kahn's algorithm). Reversing that order yields the schedule that finishes the small-numbered courses as early as possible.

将所有边反向，用最大堆（Kahn 算法）求反图的字典序**最大**拓扑序，再把它整体翻转，即得让小编号课尽量早完成的方案。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
