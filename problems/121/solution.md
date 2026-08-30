# 121 - Dynamic Range Sum Queries

## Problem / 题目

Process queries on an array: update a single value, or ask the sum of a range $[a,b]$.

在数组上处理询问：更新单个值，或询问区间 $[a,b]$ 的和。

## Idea / 思路

Use a **Fenwick tree (binary indexed tree)**, which supports point updates and prefix sums in $O(\log n)$. To update position $k$ to $u$, add the delta $u - x_k$. A range sum is $\text{prefix}(b) - \text{prefix}(a-1)$.

使用**树状数组（Fenwick）**，支持 $O(\log n)$ 的单点更新与前缀和。把位置 $k$ 更新为 $u$ 时加上增量 $u - x_k$。区间和为 $\text{prefix}(b) - \text{prefix}(a-1)$。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
