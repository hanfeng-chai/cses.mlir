# 159 - Fixed-Length Paths II

## Problem / 题目

Count the number of distinct paths in a tree whose number of edges is between $k_1$ and $k_2$ inclusive.

统计树中边数在 $k_1$ 到 $k_2$（含）之间的不同路径数。

## Idea / 思路

Use **centroid decomposition**. For each centroid $c$, every path through it has length equal to the sum of the two endpoints' depths from $c$. Collect all subtree depths (plus depth $0$ for $c$), sort them, and count pairs whose depth-sum lies in $[k_1,k_2]$ with a two-pointer sweep (range count = pairs with sum $\le k_2$ minus pairs with sum $\le k_1-1$). Then subtract, per subtree, the same count computed within that subtree alone, to remove pairs that do not actually pass through $c$. The two-pointer counting keeps the constant factor low enough for the time limit (a Fenwick-per-query version is too slow).

使用**点分治**。对每个重心 $c$，经过它的路径长度等于两端点到 $c$ 的深度之和。收集所有子树深度（再加 $c$ 自身的深度 $0$），排序后用双指针统计深度和落在 $[k_1,k_2]$ 的对数（区间计数 = 和 $\le k_2$ 的对数减去和 $\le k_1-1$ 的对数）。再按子树减去仅在该子树内部计算的同样计数，去掉实际不经过 $c$ 的对。双指针计数把常数压得足够低以满足时限（每次查询用树状数组的版本太慢）。

## Complexity / 复杂度

Centroid decomposition with sorting gives $O(n\log^2 n)$.

点分治加排序为 $O(n\log^2 n)$。
