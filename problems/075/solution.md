# 075 - Two Sets II

## Problem / 题目

Count the ways to divide the numbers $1, 2, \ldots, n$ into two sets of equal sum. Print the answer modulo $10^9+7$.

统计把数字 $1, 2, \ldots, n$ 分成两个和相等的集合的方案数。结果对 $10^9+7$ 取模。

## Idea / 思路

The total is $T = n(n+1)/2$; if $T$ is odd the answer is $0$. Otherwise each side must sum to $T/2$, so we count subsets of $\{1,\dots,n\}$ whose sum is $T/2$ using a counting knapsack: $dp[s]$ = number of subsets summing to $s$, updated coin-by-coin as $dp[s] \mathrel{+}= dp[s-i]$ (descending $s$ so each number is used once). Since swapping the two sets gives the same partition, we divide the final count by $2$ (multiply by the modular inverse of $2$).

总和 $T = n(n+1)/2$；若 $T$ 为奇数答案为 $0$。否则每一边必须和为 $T/2$，于是用计数背包统计 $\{1,\dots,n\}$ 中和为 $T/2$ 的子集数：$dp[s]$ 为和为 $s$ 的子集数，逐个数字更新 $dp[s] \mathrel{+}= dp[s-i]$（$s$ 递减保证每个数只用一次）。由于交换两个集合得到同一种划分，最后把计数除以 $2$（乘以 $2$ 的模逆元）。

## Complexity / 复杂度

The knapsack runs over $n$ numbers and sums up to $T/2$, so the time is $O(n^2)$.

背包遍历 $n$ 个数、金额到 $T/2$，因此时间为 $O(n^2)$。
