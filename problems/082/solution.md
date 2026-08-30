# 082 - Increasing Subsequence II

## Problem / 题目

Count the number of strictly increasing subsequences of an array of $n$ integers (subsequences with equal values but different positions are counted separately). Print the answer modulo $10^9+7$.

统计一个长度为 $n$ 的数组中严格递增子序列的个数（值相同但位置不同的子序列分别计数）。结果对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[i]$ be the number of increasing subsequences ending exactly at index $i$. Then $dp[i] = 1 + \sum dp[j]$ over all earlier $j$ with $x_j < x_i$ (the $1$ is the single-element subsequence). To evaluate that prefix sum quickly, compress the values and keep a Fenwick (binary indexed) tree indexed by value that stores the running sum of $dp$. For each element we query the prefix sum over strictly smaller values, set $dp[i]$, and add it back into the tree. The answer is the sum of all $dp[i]$.

设 $dp[i]$ 为恰好以下标 $i$ 结尾的递增子序列个数。则 $dp[i] = 1 + \sum dp[j]$，其中 $j$ 取遍所有满足 $x_j < x_i$ 的更早下标（那个 $1$ 是单元素子序列）。为快速求该前缀和，把值离散化，并用一个按值为索引的树状数组（Fenwick）维护 $dp$ 的累加和。对每个元素，查询严格更小值上的前缀和，定下 $dp[i]$，再把它加回树中。答案为所有 $dp[i]$ 之和。

## Complexity / 复杂度

Each element costs one Fenwick query and update, so the time is $O(n \log n)$.

每个元素一次树状数组查询与更新，因此时间为 $O(n \log n)$。
