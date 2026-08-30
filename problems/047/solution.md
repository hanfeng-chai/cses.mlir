# 047 - Factory Machines

## Problem / 题目

$n$ machines work in parallel; machine $i$ takes $k_i$ seconds per product. Find the minimum time to make $t$ products in total.

$n$ 台机器并行工作；机器 $i$ 每件产品需 $k_i$ 秒。求总共造出 $t$ 件产品的最短时间。

## Idea / 思路

Binary search the time $T$. In $T$ seconds machine $i$ makes $\lfloor T/k_i \rfloor$ products, and the total is non-decreasing in $T$, so we binary-search the smallest $T$ whose total reaches $t$. A safe upper bound is (fastest machine time) $\times\, t$.

二分时间 $T$。在 $T$ 秒内机器 $i$ 造出 $\lfloor T/k_i \rfloor$ 件，总数随 $T$ 单调不减，于是二分出总数达到 $t$ 的最小 $T$。一个安全的上界是（最快机器用时）$\times\, t$。

## Complexity / 复杂度

Each check sums over $n$ machines, so the time is $O(n \log(\text{max time}))$.

每次判定对 $n$ 台机器求和，因此时间为 $O(n \log(\text{最大时间}))$。
