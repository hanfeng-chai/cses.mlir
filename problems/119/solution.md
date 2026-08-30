# 119 - Static Range Sum Queries

## Problem / 题目

Given a static array, answer $q$ queries each asking the sum of values in a range $[a,b]$.

给定一个静态数组，回答 $q$ 个询问，每个问区间 $[a,b]$ 的元素和。

## Idea / 思路

Precompute prefix sums $pre[i] = x_1 + \dots + x_i$ once. Then the sum of any range is $pre[b] - pre[a-1]$ in constant time per query.

预处理前缀和 $pre[i] = x_1 + \dots + x_i$。则任意区间和为 $pre[b] - pre[a-1]$，每个询问常数时间。

## Complexity / 复杂度

Building prefix sums is $O(n)$ and each query is $O(1)$.

构建前缀和 $O(n)$，每个询问 $O(1)$。
