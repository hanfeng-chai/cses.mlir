# 061 - Minimizing Coins

## Problem / 题目

Given coin values and a target sum $x$, produce $x$ using the fewest coins (each coin type may be used unlimited times), or report $-1$ if impossible.

给定若干硬币面值和目标金额 $x$，用最少的硬币凑出 $x$（每种硬币可用无限次），若无法凑出则输出 $-1$。

## Idea / 思路

This is an unbounded-knapsack minimization. Let $dp[s]$ be the fewest coins summing to $s$, with $dp[0]=0$ and everything else $+\infty$. For each $s$ from $1$ to $x$, try every coin $c \le s$: $dp[s] = \min_c\, dp[s-c] + 1$. The answer is $dp[x]$, or $-1$ if it stayed infinite.

这是完全背包的最小化版本。设 $dp[s]$ 为凑出 $s$ 的最少硬币数，$dp[0]=0$，其余初始化为 $+\infty$。对每个 $s$ 从 $1$ 到 $x$，尝试每个面值 $c \le s$：$dp[s] = \min_c\, dp[s-c] + 1$。答案为 $dp[x]$，若仍为无穷则输出 $-1$。

## Complexity / 复杂度

With $n$ coins and target $x$ the time is $O(nx)$.

有 $n$ 种硬币、目标 $x$，时间为 $O(nx)$。
