# 133 - Subarray Sum Queries

## Problem / 题目

After each point update to the array, report the maximum subarray sum of the whole array (the empty subarray with sum $0$ is allowed).

每次单点更新后，报告整个数组的最大子段和（允许和为 $0$ 的空子段）。

## Idea / 思路

Use a **segment tree** where each node stores four values: the total sum, the best prefix sum, the best suffix sum, and the best subarray sum within its range. Merging two children combines them: the merged best is the larger of each child's best or the left child's best suffix joined with the right child's best prefix. After each update we refresh the affected path and read the root's best.

使用**线段树**，每个节点存四个值：总和、最优前缀和、最优后缀和、区间内最优子段和。合并两孩子时：合并后的最优子段是两孩子各自最优、或左孩子最优后缀拼右孩子最优前缀中的较大者。每次更新后刷新受影响路径并读根的最优子段和。

## Complexity / 复杂度

Each update is $O(\log n)$.

每次更新 $O(\log n)$。
