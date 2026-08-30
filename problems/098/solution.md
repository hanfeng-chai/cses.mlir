# 098 - Longest Flight Route

## Problem / 题目

In a directed acyclic graph of $n$ cities and $m$ flights, find a route from city $1$ to city $n$ visiting the maximum number of cities, and print it, or `IMPOSSIBLE`.

在一个 $n$ 城市、$m$ 航班的有向无环图中，找一条从城市 $1$ 到城市 $n$、经过城市数最多的路线并输出，或 `IMPOSSIBLE`。

## Idea / 思路

Because the graph is a DAG we can process nodes in topological order and do dynamic programming. Let $dp[v]$ be the maximum number of cities on a route from $1$ to $v$; relax $dp[v] = \max(dp[v],\, dp[u]+1)$ along each edge $u\to v$, remembering the predecessor that achieved it. If $dp[n]$ stays unreachable the answer is `IMPOSSIBLE`; otherwise follow predecessors back from $n$ to recover the route. Any longest route is accepted, so a problem-specific checker (`checker.cpp`) verifies the path uses real edges and has the optimal length.

由于图是 DAG，可按拓扑序处理节点并做动态规划。设 $dp[v]$ 为从 $1$ 到 $v$ 路线上的最多城市数；沿每条边 $u\to v$ 松弛 $dp[v] = \max(dp[v],\, dp[u]+1)$，并记下取得它的前驱。若 $dp[n]$ 仍不可达则答案为 `IMPOSSIBLE`；否则从 $n$ 沿前驱回溯重建路线。任意最长路线都被接受，故题目专用 checker（`checker.cpp`）校验路径用真实边且长度最优。

## Complexity / 复杂度

The topological DP runs in $O(n+m)$.

拓扑 DP 运行在 $O(n+m)$。
