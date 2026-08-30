# 100 - Investigation

## Problem / 题目

For the cheapest flight route from city $1$ to city $n$, report four things: the minimum price, the number of minimum-price routes (mod $10^9+7$), and the minimum and maximum number of flights among minimum-price routes.

对从城市 $1$ 到城市 $n$ 的最便宜航线，报告四个量：最小价格、最小价格路线的数量（对 $10^9+7$ 取模）、以及最小价格路线中航班数的最小值与最大值。

## Idea / 思路

Run Dijkstra, but carry four quantities per city: the shortest distance, the count of shortest paths, and the minimum and maximum edge counts among them. When an edge $u\to v$ gives a strictly shorter distance, copy $u$'s statistics (incrementing the edge counts). When it gives an equal distance, **merge**: add to the count, take the smaller min-edges and the larger max-edges. Because edge prices are positive, every contributor to a city has a strictly smaller distance and is finalized first, so the merged values are correct when the city is popped.

跑 Dijkstra，但每座城市携带四个量：最短距离、最短路条数、以及其中航班数的最小值与最大值。当边 $u\to v$ 给出严格更短的距离时，复制 $u$ 的统计（航班数加一）。当给出相等距离时，**合并**：条数相加、最小航班数取更小、最大航班数取更大。由于价格为正，某城的每个贡献者距离都严格更小、更早定型，因此该城弹出时合并值已正确。

## Complexity / 复杂度

Dijkstra runs in $O((n+m)\log n)$.

Dijkstra 运行在 $O((n+m)\log n)$。
