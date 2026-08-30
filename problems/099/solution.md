# 099 - Game Routes

## Problem / 题目

In a directed acyclic graph of $n$ levels and $m$ teleporters, count the number of ways to get from level $1$ to level $n$, modulo $10^9+7$.

在一个 $n$ 关卡、$m$ 传送门的有向无环图中，统计从关卡 $1$ 到关卡 $n$ 的方案数，对 $10^9+7$ 取模。

## Idea / 思路

Process levels in topological order. Let $dp[v]$ be the number of routes from level $1$ to level $v$, with $dp[1]=1$. Whenever we relax an edge $u\to v$, add $dp[u]$ into $dp[v]$. Because every predecessor of $v$ is finalized before $v$ is reached in topological order, $dp[n]$ ends up being the total number of routes.

按拓扑序处理关卡。设 $dp[v]$ 为从关卡 $1$ 到 $v$ 的路线数，$dp[1]=1$。每次松弛边 $u\to v$ 时把 $dp[u]$ 累加进 $dp[v]$。由于拓扑序中 $v$ 的每个前驱都在到达 $v$ 之前定型，最终 $dp[n]$ 即为路线总数。

## Complexity / 复杂度

The topological DP runs in $O(n+m)$.

拓扑 DP 运行在 $O(n+m)$。
