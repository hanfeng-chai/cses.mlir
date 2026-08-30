# 223 - Minimum Euclidean Distance

## Problem / 题目
Find the minimum squared Euclidean distance between two distinct points among $n$ points.

求 $n$ 个点中两个不同点的最小欧氏距离的平方。

## Idea / 思路
Sweep the points sorted by $x$, keeping a set of recent points ordered by $y$. For each new point, discard points whose $x$-distance squared already exceeds the current best, then check only the candidates within a $y$-band of width $\sqrt{\text{best}}$. This classic sweep yields the closest pair in near-linear time.

按 $x$ 排序扫描，维护一个按 $y$ 有序的近期点集合。处理每个新点时，先剔除 $x$ 距离平方已超过当前最优的点，再只检查 $y$ 方向宽度 $\sqrt{\text{best}}$ 带内的候选。这一经典扫描在近线性时间内求出最近点对。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
