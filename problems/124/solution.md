# 124 - Range Update Queries

## Problem / 题目

Process queries: increase every value in a range $[a,b]$ by $u$, or ask the current value at a single position $k$.

处理询问：把区间 $[a,b]$ 的每个值加 $u$，或询问单个位置 $k$ 的当前值。

## Idea / 思路

This is the dual of range-sum-with-point-update, solved with a **difference array on a Fenwick tree**. A range add $[a,b]$ of $u$ becomes two point updates: $+u$ at $a$ and $-u$ at $b+1$. The value at position $k$ is then the original value plus the prefix sum of the difference array up to $k$.

这是"区间和+单点更新"的对偶，用**树状数组上的差分**求解。对 $[a,b]$ 加 $u$ 化为两次单点更新：在 $a$ 处 $+u$、在 $b+1$ 处 $-u$。位置 $k$ 的值即原值加上差分数组到 $k$ 的前缀和。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
