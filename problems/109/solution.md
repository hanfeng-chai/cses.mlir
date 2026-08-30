# 109 - Coin Collector

## Problem / 题目

Each room holds some coins. Moving through one-way tunnels and freely choosing start and end, collect the maximum total number of coins (a room's coins count once even if revisited).

每个房间有一些金币。沿单向隧道移动、自由选择起点终点，收集尽可能多的金币总数（房间金币即使重复经过也只计一次）。

## Idea / 思路

Inside a strongly connected component you can reach every room, so you collect all its coins. Contract each **SCC** into a single node whose weight is the sum of its rooms' coins; the contracted graph is a DAG. The answer is the maximum-weight path in this DAG, found by dynamic programming over the components in topological order: $dp[c] = sum[c] + \max(dp[\text{predecessor}])$. Kosaraju conveniently numbers components in topological order, so a single forward sweep suffices.

在一个强连通分量内你能到达每个房间，因此能收齐它的所有金币。把每个 **SCC** 缩成一个权值为其房间金币之和的点，缩点后的图是 DAG。答案是该 DAG 上的最大权路径，用按拓扑序的 DP 求：$dp[c] = sum[c] + \max(dp[\text{前驱}])$。Kosaraju 恰好按拓扑序给分量编号，故一次正向扫描即可。

## Complexity / 复杂度

SCC plus the DAG DP run in $O(n+m)$.

SCC 加 DAG DP 运行在 $O(n+m)$。
