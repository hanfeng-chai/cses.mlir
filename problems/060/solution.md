# 060 - Dice Combinations

## Problem / 题目

Count the number of ways to build the sum $n$ by throwing a die one or more times; each throw gives a value from $1$ to $6$ and **order matters**. Print the answer modulo $10^9+7$.

统计用一个骰子掷一次或多次得到总和 $n$ 的方案数；每次掷出 $1$ 到 $6$ 的点数，且**顺序不同算不同方案**。结果对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[i]$ be the number of ordered ways to reach sum $i$. The last throw was some value $j \in \{1,\dots,6\}$, so $dp[i] = \sum_{j=1}^{6} dp[i-j]$ with $dp[0]=1$ (the empty sequence). Because we sum over the value of the *last* throw, every ordering is counted separately.

设 $dp[i]$ 为得到总和 $i$ 的有序方案数。最后一次掷出的点数为某个 $j \in \{1,\dots,6\}$，于是 $dp[i] = \sum_{j=1}^{6} dp[i-j]$，初值 $dp[0]=1$（空序列）。因为我们对*最后一次*掷出的点数求和，所以每种顺序都被分别计数。

## Complexity / 复杂度

There are $n$ states and each takes a constant six terms, so the time is $O(n)$.

共有 $n$ 个状态，每个只需常数六项，因此时间为 $O(n)$。
