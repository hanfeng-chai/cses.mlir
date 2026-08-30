# 062 - Coin Combinations I

## Problem / 题目

Count the number of **ordered** ways (sequences) to form the sum $x$ from the given coins, each usable unlimited times. Print the answer modulo $10^9+7$.

统计用给定硬币（每种可无限次使用）凑出金额 $x$ 的**有序**方案数（即序列数）。结果对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[s]$ be the number of ordered ways to make $s$, with $dp[0]=1$. We iterate the sum $s$ in the outer loop and the coins in the inner loop: $dp[s] = \sum_{c} dp[s-c]$. Putting the sum outside means we decide the value of the *next* coin in the sequence at each step, so $2+3$ and $3+2$ are counted as different.

设 $dp[s]$ 为凑出 $s$ 的有序方案数，$dp[0]=1$。外层枚举金额 $s$、内层枚举硬币：$dp[s] = \sum_{c} dp[s-c]$。把金额放在外层意味着每一步决定序列里*下一枚*硬币的面值，因此 $2+3$ 与 $3+2$ 被算作不同方案。

## Complexity / 复杂度

The double loop over $x$ and $n$ coins gives $O(nx)$.

对 $x$ 与 $n$ 种硬币的双重循环为 $O(nx)$。
