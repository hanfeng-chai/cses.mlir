# 064 - Removing Digits

## Problem / 题目

Starting from an integer $n$, on each step subtract one of its current digits. Find the minimum number of steps to reach $0$.

从整数 $n$ 出发，每一步减去它当前的某一位数字。求到达 $0$ 的最少步数。

## Idea / 思路

Let $dp[i]$ be the minimum steps to reduce $i$ to $0$, with $dp[0]=0$. From $i$ we may subtract any nonzero digit $d$ that appears in $i$, giving $dp[i] = \min_d\, dp[i-d] + 1$. Filling $dp$ from $1$ up to $n$ gives the answer $dp[n]$. (A greedy "always subtract the largest digit" also works here, but the DP is simple and obviously correct.)

设 $dp[i]$ 为把 $i$ 减到 $0$ 的最少步数，$dp[0]=0$。从 $i$ 可以减去它包含的任意非零数字 $d$，于是 $dp[i] = \min_d\, dp[i-d] + 1$。从 $1$ 递推到 $n$ 即得答案 $dp[n]$。（这里"每次减最大数字"的贪心也成立，但 DP 简单且显然正确。）

## Complexity / 复杂度

Each of the $n$ states inspects at most a handful of digits, so the time is $O(n \log n)$.

$n$ 个状态每个只检查常数个数字位，因此时间为 $O(n \log n)$。
