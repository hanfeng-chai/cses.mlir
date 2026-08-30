# 070 - Longest Common Subsequence

## Problem / 题目

Given two arrays, find a longest common subsequence: print its length and one example sequence. Any valid longest sequence is accepted.

给定两个数组，求一个最长公共子序列：输出长度和一个例子。任意一个合法的最长序列都被接受。

## Idea / 思路

Let $dp[i][j]$ be the LCS length of the prefixes $a[1..i]$ and $b[1..j]$. If $a_i = b_j$ then $dp[i][j] = dp[i-1][j-1] + 1$, otherwise $dp[i][j] = \max(dp[i-1][j],\, dp[i][j-1])$. Reconstruct one example by walking back from $(n,m)$: on a match take the element and move diagonally, else move toward the larger neighbour. Because many optimal subsequences may exist, we ship a problem-specific checker (`checker.cpp`) that accepts the output if its length equals the optimum **and** it really is a subsequence of both arrays.

设 $dp[i][j]$ 为前缀 $a[1..i]$ 与 $b[1..j]$ 的 LCS 长度。若 $a_i = b_j$ 则 $dp[i][j] = dp[i-1][j-1] + 1$，否则 $dp[i][j] = \max(dp[i-1][j],\, dp[i][j-1])$。从 $(n,m)$ 回溯重建一个例子：相等时取该元素并沿对角线走，否则朝较大的邻居走。由于最优子序列可能有很多，我们提供题目专用 checker（`checker.cpp`），当输出长度等于最优值**且**确实是两数组的公共子序列时判正确。

## Complexity / 复杂度

Filling the table and reconstructing are both $O(nm)$.

填表与回溯都是 $O(nm)$。
