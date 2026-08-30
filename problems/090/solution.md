# 090 - Shortest Routes I

## Problem / 题目

Given a directed weighted graph with $n$ cities and $m$ one-way flights (positive lengths), print the shortest distance from city $1$ to every city.

给定一个有 $n$ 座城市、$m$ 条单向航班（正权）的有向带权图，输出从城市 $1$ 到每座城市的最短距离。

## Idea / 思路

With non-negative edge weights this is Dijkstra's algorithm. Keep tentative distances, repeatedly extract the closest unfinished city from a min-heap, and relax its outgoing edges. Each city is finalized when first popped with its true distance. Distances can reach about $10^5 \cdot 10^9$, so we use 64-bit integers.

边权非负，用 Dijkstra 算法。维护暂定距离，反复从小根堆取出最近的未完成城市，并松弛它的出边。每座城市在第一次以真实距离弹出时定型。距离可达约 $10^5 \cdot 10^9$，因此使用 64 位整数。

## Complexity / 复杂度

With a binary heap the time is $O((n+m)\log n)$.

使用二叉堆时间为 $O((n+m)\log n)$。
