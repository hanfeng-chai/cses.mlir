# 132 - Range Interval Queries

## Problem / 题目

For each query, count the indices $i$ with $a \le i \le b$ and $c \le x_i \le d$.

对每个询问，统计满足 $a \le i \le b$ 且 $c \le x_i \le d$ 的下标 $i$ 个数。

## Idea / 思路

This is a 2D counting query (index range × value range). We answer it **offline**: each query splits into two prefix-index events, at $b$ (added) and $a-1$ (subtracted), each asking how many already-inserted values lie in $[c,d]$. Sweep the index from $1$ to $n$, inserting $x_i$ into a Fenwick tree indexed by compressed value, and resolve every event whose prefix index has been reached. Combining the signed contributions gives each query's answer.

这是二维计数（下标范围 × 值范围）。我们**离线**作答：每个询问拆成两个前缀下标事件，在 $b$ 处（加）与 $a-1$ 处（减），各问已插入值中有多少落在 $[c,d]$。将下标从 $1$ 扫到 $n$，把 $x_i$ 插入按压缩值为下标的树状数组，并处理所有已到达其前缀下标的事件。合并带符号贡献即得每个询问答案。

## Complexity / 复杂度

Sorting events and Fenwick operations give $O((n+q)\log n)$.

事件排序加树状数组操作为 $O((n+q)\log n)$。
