# 115 - Download Speed

## Problem / 题目

In a network with directed capacities, find the maximum data speed from the server (computer $1$) to computer $n$.

在一个有向带容量的网络中，求从服务器（计算机 $1$）到计算机 $n$ 的最大数据速度。

## Idea / 思路

The maximum download speed is the **maximum flow** from source $1$ to sink $n$. We use Dinic's algorithm: repeatedly build a level graph with BFS (shortest residual distances), then send blocking flow along level-respecting paths with DFS, until the sink is no longer reachable in the residual graph. Capacities can be large, so the flow value is accumulated in 64-bit integers.

最大下载速度就是从源 $1$ 到汇 $n$ 的**最大流**。我们用 Dinic 算法：反复用 BFS 建分层图（残量最短距离），再用 DFS 沿遵守层次的路径推送阻塞流，直到残量图中汇不可达。容量可能很大，故流值用 64 位整数累加。

## Complexity / 复杂度

Dinic's algorithm runs in $O(V^2 E)$ in general, far faster on these sparse graphs.

Dinic 算法一般为 $O(V^2 E)$，在这些稀疏图上快得多。
