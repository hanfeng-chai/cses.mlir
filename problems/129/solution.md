# 129 - Prefix Sum Queries

## Problem / 题目

Process queries: update a value, or ask the maximum prefix sum within a range $[a,b]$ (the empty prefix with sum $0$ is allowed).

处理询问：更新一个值，或询问区间 $[a,b]$ 内的最大前缀和（允许和为 $0$ 的空前缀）。

## Idea / 思路

Use a **segment tree** where each node stores the total sum of its range and its best prefix sum. Merging a left child $L$ and right child $R$ gives total $= L.\text{sum}+R.\text{sum}$ and best prefix $= \max(L.\text{prefix},\, L.\text{sum}+R.\text{prefix})$ — either the best prefix stays inside $L$, or it spans all of $L$ plus a prefix of $R$. Point updates and range queries both combine these nodes.

使用**线段树**，每个节点存其区间总和与最优前缀和。合并左孩子 $L$ 与右孩子 $R$：总和 $= L.\text{sum}+R.\text{sum}$，最优前缀 $= \max(L.\text{prefix},\, L.\text{sum}+R.\text{prefix})$——最优前缀要么落在 $L$ 内，要么跨越整个 $L$ 再加 $R$ 的一个前缀。单点更新与区间询问都合并这些节点。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
