# 067 - Array Description

## Problem / 题目

An array of $n$ integers, each between $1$ and $m$, has adjacent values differing by at most $1$. Some entries are known and some are unknown ($0$). Count the arrays matching the description, modulo $10^9+7$.

一个长度为 $n$ 的数组，每个元素在 $1$ 到 $m$ 之间，相邻元素之差至多为 $1$。部分元素已知、部分未知（用 $0$ 表示）。统计符合描述的数组个数，对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[i][v]$ be the number of valid ways to fill the first $i$ elements with the $i$-th equal to $v$. Since adjacent values differ by at most $1$, $dp[i][v] = dp[i-1][v-1] + dp[i-1][v] + dp[i-1][v+1]$, restricted to values $v$ allowed at position $i$ (all of $1..m$ if unknown, otherwise just the fixed value). The answer sums $dp[n][\cdot]$ over all $v$.

设 $dp[i][v]$ 为前 $i$ 个元素合法、且第 $i$ 个等于 $v$ 的方案数。由于相邻之差至多为 $1$，$dp[i][v] = dp[i-1][v-1] + dp[i-1][v] + dp[i-1][v+1]$，其中 $v$ 限定为位置 $i$ 允许的取值（未知则为 $1..m$ 全部，否则只有固定值）。答案为所有 $v$ 上 $dp[n][\cdot]$ 之和。

## Complexity / 复杂度

There are $n \cdot m$ states each updated in constant time, so the time is $O(nm)$.

共 $n \cdot m$ 个状态，每个常数时间更新，因此时间为 $O(nm)$。
