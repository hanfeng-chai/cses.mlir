# 135 - Distinct Values Queries

## Problem / 题目

For each query, report the number of distinct values in a range $[a,b]$ of a static array.

对每个询问，报告静态数组区间 $[a,b]$ 内不同值的个数。

## Idea / 思路

Answer the queries **offline**, sorted by right endpoint $b$. Sweep $i$ from $1$ to $n$, keeping in a Fenwick tree a $1$ at the **last** position of each value seen so far: when value $x_i$ reappears, move its mark from its previous position to $i$. After processing up to $b$, the number of distinct values in $[a,b]$ equals the count of marks in $[a,b]$, a Fenwick range sum.

按右端点 $b$ 排序后**离线**作答。将 $i$ 从 $1$ 扫到 $n$，在树状数组里为每个已见值的**最后**出现位置保留一个 $1$：当值 $x_i$ 再次出现时，把它的标记从上一个位置移到 $i$。处理到 $b$ 后，$[a,b]$ 内不同值的个数等于 $[a,b]$ 内标记数，即一次树状数组区间和。

## Complexity / 复杂度

Sorting plus Fenwick operations give $O((n+q)\log n)$.

排序加树状数组操作为 $O((n+q)\log n)$。
