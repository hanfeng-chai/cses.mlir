# 134 - Subarray Sum Queries II

## Problem / 题目

For each query, report the maximum subarray sum within a range $[a,b]$ (empty subarray with sum $0$ allowed).

对每个询问，报告区间 $[a,b]$ 内的最大子段和（允许和为 $0$ 的空子段）。

## Idea / 思路

The same segment tree as the point-update version — each node storing (total, best prefix, best suffix, best subarray) — also supports range queries. We gather the $O(\log n)$ canonical nodes covering $[a,b]$, merge them left to right with the same combine rule, and read the resulting best subarray value.

与单点更新版相同的线段树——每个节点存（总和、最优前缀、最优后缀、最优子段）——同样支持区间询问。我们收集覆盖 $[a,b]$ 的 $O(\log n)$ 个规范节点，用同样的合并规则从左到右合并，读取结果的最优子段值。

## Complexity / 复杂度

Each query is $O(\log n)$.

每个询问 $O(\log n)$。
