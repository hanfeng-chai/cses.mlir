# 123 - Range Xor Queries

## Problem / 题目

Given a static array, answer $q$ queries each asking the xor of values in a range $[a,b]$.

给定一个静态数组，回答 $q$ 个询问，每个问区间 $[a,b]$ 的异或和。

## Idea / 思路

Because xor is its own inverse, prefix xors work just like prefix sums. Precompute $pre[i] = x_1 \oplus \dots \oplus x_i$; the xor of a range is $pre[b] \oplus pre[a-1]$, since the shared prefix cancels.

由于异或自逆，前缀异或和前缀和用法相同。预处理 $pre[i] = x_1 \oplus \dots \oplus x_i$；区间异或为 $pre[b] \oplus pre[a-1]$，因为公共前缀相互抵消。

## Complexity / 复杂度

Building is $O(n)$ and each query is $O(1)$.

构建 $O(n)$，每个询问 $O(1)$。
