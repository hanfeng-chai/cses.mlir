# 118 - Distinct Routes

## Problem / 题目

Each teleporter may be used at most once across all days. Starting each day at room $1$ and reaching room $n$, find the maximum number of days (edge-disjoint routes) and print each route.

每个传送门在所有天里至多用一次。每天从房间 $1$ 出发到达房间 $n$，求最多能玩几天（边不相交路线数）并输出每条路线。

## Idea / 思路

The maximum number of edge-disjoint $1\to n$ routes equals the **maximum flow** with every teleporter given capacity $1$. We run Dinic; the flow value is the number of days. Because Dinic's flow is a sum of augmenting paths it is acyclic, so we recover the routes greedily: from room $1$, repeatedly follow an unused saturated edge until reaching room $n$, consuming each edge once. Any optimal set of edge-disjoint routes is accepted, so a problem-specific checker (`checker.cpp`) verifies the routes go $1\to n$, use real edges, and never share a teleporter.

边不相交的 $1\to n$ 路线最大数等于每个传送门容量为 $1$ 时的**最大流**。我们运行 Dinic；流值即天数。由于 Dinic 的流是增广路之和、无环，故可贪心还原路线：从房间 $1$ 反复沿一条未用的饱和边走到房间 $n$，每条边消耗一次。任意最优的边不相交路线集合都被接受，故题目专用 checker（`checker.cpp`）校验路线从 $1$ 到 $n$、用真实边、且不共用传送门。

## Complexity / 复杂度

Unit-capacity Dinic plus path extraction runs well within the limits for $n \le 500$.

单位容量 Dinic 加路径提取对 $n \le 500$ 远在时限内。
